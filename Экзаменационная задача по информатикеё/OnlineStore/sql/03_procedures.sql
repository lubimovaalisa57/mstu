-- Процедура создания пустого заказа
CREATE OR REPLACE PROCEDURE create_empty_order(
    IN p_user_id INTEGER,
    OUT p_order_id INTEGER
)
LANGUAGE plpgsql
AS $$
BEGIN
    -- Проверяем существование пользователя
    IF NOT EXISTS (SELECT 1 FROM users WHERE user_id = p_user_id) THEN
        RAISE EXCEPTION 'Пользователь не найден';
END IF;

INSERT INTO orders (user_id, status, total_price)
VALUES (p_user_id, 'pending', 0)
    RETURNING order_id INTO p_order_id;

-- Логируем создание заказа
INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, details)
VALUES ('order', p_order_id, 'insert', p_user_id, 'Создан новый заказ');

RAISE NOTICE 'Создан заказ ID: % для пользователя ID: %', p_order_id, p_user_id;
END;
$$;

-- Процедура добавления товара в заказ
CREATE OR REPLACE PROCEDURE add_product_to_order(
    IN p_order_id INTEGER,
    IN p_product_id INTEGER,
    IN p_quantity INTEGER,
    IN p_user_id INTEGER
)
LANGUAGE plpgsql
AS $$
DECLARE
v_price DECIMAL;
    v_stock INTEGER;
    v_current_status VARCHAR;
    v_product_name VARCHAR;
    v_order_exists BOOLEAN;
BEGIN
    -- Проверяем существование заказа
SELECT EXISTS(SELECT 1 FROM orders WHERE order_id = p_order_id AND user_id = p_user_id)
INTO v_order_exists;

IF NOT v_order_exists THEN
        RAISE EXCEPTION 'Заказ не найден или не принадлежит пользователю';
END IF;

    -- Проверяем статус заказа
SELECT status INTO v_current_status
FROM orders WHERE order_id = p_order_id;

IF v_current_status != 'pending' THEN
        RAISE EXCEPTION 'Можно добавлять товары только в заказы со статусом pending';
END IF;

    -- Получаем цену, количество и название
SELECT price, stock_quantity, name INTO v_price, v_stock, v_product_name
FROM products WHERE product_id = p_product_id;

IF NOT FOUND THEN
        RAISE EXCEPTION 'Продукт не найден';
END IF;

    IF v_stock < p_quantity THEN
        RAISE EXCEPTION 'Недостаточно товара на складе. Доступно: %, запрошено: %', v_stock, p_quantity;
END IF;

    -- Добавляем или обновляем товар в заказе
INSERT INTO order_items (order_id, product_id, quantity, price)
VALUES (p_order_id, p_product_id, p_quantity, v_price)
    ON CONFLICT (order_id, product_id)
    DO UPDATE SET quantity = order_items.quantity + p_quantity;

-- Обновляем общую сумму заказа
UPDATE orders
SET total_price = total_price + (v_price * p_quantity),
    updated_at = CURRENT_TIMESTAMP
WHERE order_id = p_order_id;

-- Уменьшаем количество на складе
UPDATE products
SET stock_quantity = stock_quantity - p_quantity
WHERE product_id = p_product_id;

-- Логируем действие
INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, details)
VALUES ('order', p_order_id, 'update', p_user_id,
        format('Добавлен товар: %s (ID: %), количество: %', v_product_name, p_product_id, p_quantity));

RAISE NOTICE 'Товар ID: % добавлен в заказ ID: %', p_product_id, p_order_id;

EXCEPTION
    WHEN OTHERS THEN
        RAISE;
END;
$$;

-- Процедура утверждения заказа менеджером
CREATE OR REPLACE PROCEDURE approve_order(
    IN p_order_id INTEGER,
    IN p_manager_id INTEGER
)
LANGUAGE plpgsql
AS $$
DECLARE
v_old_status VARCHAR;
    v_customer_name VARCHAR;
    v_order_exists BOOLEAN;
BEGIN
    -- Проверяем, что пользователь - менеджер
    IF NOT EXISTS (SELECT 1 FROM users WHERE user_id = p_manager_id AND role = 'manager') THEN
        RAISE EXCEPTION 'Только менеджер может утверждать заказы';
END IF;

    -- Получаем текущий статус и информацию о заказе
SELECT o.status, u.name INTO v_old_status, v_customer_name
FROM orders o
         JOIN users u ON o.user_id = u.user_id
WHERE o.order_id = p_order_id;

IF NOT FOUND THEN
        RAISE EXCEPTION 'Заказ не найден';
END IF;

    IF v_old_status != 'pending' THEN
        RAISE EXCEPTION 'Можно утверждать только заказы со статусом pending. Текущий статус: %', v_old_status;
END IF;

    -- Обновляем статус
UPDATE orders SET status = 'processing'
WHERE order_id = p_order_id;

-- Сохраняем историю
INSERT INTO order_status_history (order_id, old_status, new_status, changed_by)
VALUES (p_order_id, v_old_status, 'processing', p_manager_id);

-- Логируем действие
INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, details)
VALUES ('order', p_order_id, 'update', p_manager_id,
        format('Заказ утвержден менеджером. Покупатель: %s', v_customer_name));

RAISE NOTICE 'Заказ ID: % утвержден менеджером ID: %', p_order_id, p_manager_id;
END;
$$;

-- Процедура обновления статуса заказа
CREATE OR REPLACE PROCEDURE update_order_status(
    IN p_order_id INTEGER,
    IN p_new_status VARCHAR,
    IN p_changed_by INTEGER
)
LANGUAGE plpgsql
AS $$
DECLARE
v_old_status VARCHAR;
    v_user_id INTEGER;
    v_user_role VARCHAR;
    v_can_change BOOLEAN := FALSE;
BEGIN
    -- Получаем информацию о заказе и пользователе
SELECT o.status, o.user_id, u.role INTO v_old_status, v_user_id, v_user_role
FROM orders o
         JOIN users u ON u.user_id = p_changed_by
WHERE o.order_id = p_order_id;

IF NOT FOUND THEN
        RAISE EXCEPTION 'Заказ не найден';
END IF;

    -- Проверяем права доступа
    IF v_user_role = 'admin' THEN
        v_can_change := TRUE;
    ELSIF v_user_role = 'manager' THEN
        IF p_new_status IN ('processing', 'completed') AND v_old_status IN ('pending', 'processing') THEN
            v_can_change := TRUE;
END IF;
    ELSIF v_user_role = 'customer' THEN
        IF v_user_id = p_changed_by AND p_new_status = 'canceled' AND v_old_status = 'pending' THEN
            v_can_change := TRUE;
END IF;
END IF;

    IF NOT v_can_change THEN
        RAISE EXCEPTION 'У вас нет прав для изменения статуса заказа';
END IF;

    -- Проверяем бизнес-правила
    IF v_old_status = 'completed' AND p_new_status = 'canceled' THEN
        RAISE EXCEPTION 'Завершенный заказ нельзя отменить';
END IF;

    IF v_old_status = 'canceled' AND p_new_status != 'canceled' THEN
        RAISE EXCEPTION 'Отмененный заказ нельзя изменить';
END IF;

    -- Обновляем статус
UPDATE orders SET
                  status = p_new_status,
                  updated_at = CURRENT_TIMESTAMP
WHERE order_id = p_order_id;

-- Сохраняем историю
INSERT INTO order_status_history (order_id, old_status, new_status, changed_by)
VALUES (p_order_id, v_old_status, p_new_status, p_changed_by);

-- Логируем действие
INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, details)
VALUES ('order', p_order_id, 'update', p_changed_by,
        format('Статус изменен: %s -> %s', v_old_status, p_new_status));

RAISE NOTICE 'Статус заказа ID: % изменен: % -> %', p_order_id, v_old_status, p_new_status;
END;
$$;

-- Процедура обработки возврата заказа
CREATE OR REPLACE PROCEDURE process_order_return(
    IN p_order_id INTEGER,
    IN p_customer_id INTEGER
)
LANGUAGE plpgsql
AS $$
DECLARE
v_order_status VARCHAR;
    v_order_date TIMESTAMP;
    v_total_price DECIMAL;
    v_days_passed INTEGER;
    v_can_return BOOLEAN;
BEGIN
    -- Получаем информацию о заказе
SELECT status, order_date, total_price INTO v_order_status, v_order_date, v_total_price
FROM orders
WHERE order_id = p_order_id AND user_id = p_customer_id;

IF NOT FOUND THEN
        RAISE EXCEPTION 'Заказ не найден или не принадлежит вам';
END IF;

    -- Проверяем возможность возврата
    v_days_passed := EXTRACT(DAY FROM (CURRENT_TIMESTAMP - v_order_date));
    v_can_return := v_order_status = 'completed' AND v_days_passed <= 30;

    IF NOT v_can_return THEN
        RAISE EXCEPTION 'Возврат невозможен. Статус: %, прошло дней: %', v_order_status, v_days_passed;
END IF;

    -- Обновляем статус заказа
UPDATE orders SET status = 'returned'
WHERE order_id = p_order_id;

-- Сохраняем историю
INSERT INTO order_status_history (order_id, old_status, new_status, changed_by)
VALUES (p_order_id, v_order_status, 'returned', p_customer_id);

-- Возвращаем товары на склад
UPDATE products p
SET stock_quantity = p.stock_quantity + oi.quantity
    FROM order_items oi
WHERE oi.order_id = p_order_id AND p.product_id = oi.product_id;

-- Логируем действие
INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, details)
VALUES ('order', p_order_id, 'update', p_customer_id,
        format('Заказ возвращен. Сумма возврата: %, прошло дней: %', v_total_price, v_days_passed));

-- Создаем запись о возврате платежа
INSERT INTO payments (order_id, amount, payment_method, payment_status, details)
VALUES (p_order_id, v_total_price, 'refund', 'completed',
        format('Возврат средств по заказу ID: %', p_order_id));

RAISE NOTICE 'Заказ ID: % возвращен. Сумма возврата: %', p_order_id, v_total_price;
END;
$$;

-- Процедура создания нового продукта
CREATE OR REPLACE PROCEDURE create_product(
    IN p_name VARCHAR,
    IN p_price DECIMAL,
    IN p_stock_quantity INTEGER,
    IN p_admin_id INTEGER
)
LANGUAGE plpgsql
AS $$
DECLARE
v_product_id INTEGER;
BEGIN
    -- Проверяем, что пользователь - администратор
    IF NOT EXISTS (SELECT 1 FROM users WHERE user_id = p_admin_id AND role = 'admin') THEN
        RAISE EXCEPTION 'Только администратор может создавать продукты';
END IF;

INSERT INTO products (name, price, stock_quantity)
VALUES (p_name, p_price, p_stock_quantity)
    RETURNING product_id INTO v_product_id;

-- Логируем действие
INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, details)
VALUES ('product', v_product_id, 'insert', p_admin_id,
        format('Создан продукт: %s, цена: %, количество: %', p_name, p_price, p_stock_quantity));

RAISE NOTICE 'Создан продукт ID: %, название: %', v_product_id, p_name;
END;
$$;

-- Процедура удаления продукта
CREATE OR REPLACE PROCEDURE delete_product(
    IN p_product_id INTEGER,
    IN p_admin_id INTEGER
)
LANGUAGE plpgsql
AS $$
DECLARE
v_product_name VARCHAR;
    v_has_orders BOOLEAN;
BEGIN
    -- Проверяем, что пользователь - администратор
    IF NOT EXISTS (SELECT 1 FROM users WHERE user_id = p_admin_id AND role = 'admin') THEN
        RAISE EXCEPTION 'Только администратор может удалять продукты';
END IF;

    -- Получаем название продукта
SELECT name INTO v_product_name
FROM products WHERE product_id = p_product_id;

IF NOT FOUND THEN
        RAISE EXCEPTION 'Продукт не найден';
END IF;

    -- Проверяем, есть ли заказы с этим продуктом
SELECT EXISTS(
    SELECT 1 FROM order_items WHERE product_id = p_product_id
) INTO v_has_orders;

IF v_has_orders THEN
        RAISE EXCEPTION 'Нельзя удалить продукт, который есть в заказах';
END IF;

    -- Удаляем продукт
DELETE FROM products WHERE product_id = p_product_id;

-- Логируем действие
INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, details)
VALUES ('product', p_product_id, 'delete', p_admin_id,
        format('Удален продукт: %s (ID: %)', v_product_name, p_product_id));

RAISE NOTICE 'Удален продукт ID: %, название: %', p_product_id, v_product_name;
END;
$$;