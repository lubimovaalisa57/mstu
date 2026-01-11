-- Триггер для автоматического обновления updated_at в таблице orders
CREATE OR REPLACE FUNCTION update_orders_timestamp()
RETURNS TRIGGER AS $$
BEGIN
    NEW.updated_at = CURRENT_TIMESTAMP;
RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_orders_update_timestamp
    BEFORE UPDATE ON orders
    FOR EACH ROW
    EXECUTE FUNCTION update_orders_timestamp();

-- Триггер для логирования изменений статусов заказов
CREATE OR REPLACE FUNCTION log_order_status_change()
RETURNS TRIGGER AS $$
BEGIN
    IF OLD.status != NEW.status THEN
        INSERT INTO order_status_history (order_id, old_status, new_status, changed_by)
        VALUES (NEW.order_id, OLD.status, NEW.status,
                COALESCE(current_setting('app.user_id')::INTEGER, 0));
END IF;
RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_order_status_change
    AFTER UPDATE OF status ON orders
    FOR EACH ROW
    EXECUTE FUNCTION log_order_status_change();

-- Триггер для обновления total_price при изменении цены продукта
CREATE OR REPLACE FUNCTION update_order_prices_on_product_change()
RETURNS TRIGGER AS $$
BEGIN
    IF OLD.price != NEW.price THEN
        -- Обновляем цену в order_items
UPDATE order_items oi
SET price = NEW.price
WHERE oi.product_id = NEW.product_id;

-- Пересчитываем total_price для всех заказов с этим продуктом
UPDATE orders o
SET total_price = (
    SELECT SUM(oi.quantity * oi.price)
    FROM order_items oi
    WHERE oi.order_id = o.order_id
)
WHERE o.order_id IN (
    SELECT DISTINCT order_id
    FROM order_items
    WHERE product_id = NEW.product_id
);
END IF;
RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_update_order_prices
    AFTER UPDATE OF price ON products
    FOR EACH ROW
    EXECUTE FUNCTION update_order_prices_on_product_change();

-- Триггер для аудита изменений в таблице products
CREATE OR REPLACE FUNCTION audit_products_changes()
RETURNS TRIGGER AS $$
DECLARE
v_operation VARCHAR;
    v_user_id INTEGER;
BEGIN
    v_user_id := COALESCE(current_setting('app.user_id')::INTEGER, 0);

    IF TG_OP = 'INSERT' THEN
        v_operation := 'insert';
    ELSIF TG_OP = 'UPDATE' THEN
        v_operation := 'update';
    ELSIF TG_OP = 'DELETE' THEN
        v_operation := 'delete';
END IF;

INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, details)
VALUES ('product',
        COALESCE(NEW.product_id, OLD.product_id),
        v_operation,
        v_user_id,
        CASE
            WHEN TG_OP = 'INSERT' THEN format('Создан продукт: %s', NEW.name)
            WHEN TG_OP = 'UPDATE' THEN
                format('Обновлен продукт: %s. Изменения: %s',
                       COALESCE(NEW.name, OLD.name),
                       CASE
                           WHEN OLD.name != NEW.name THEN 'name, ' ELSE '' END ||
                       CASE
                           WHEN OLD.price != NEW.price THEN
                               format('price: % -> %, ', OLD.price, NEW.price)
                           ELSE '' END ||
                       CASE
                           WHEN OLD.stock_quantity != NEW.stock_quantity THEN
                               format('stock: % -> %', OLD.stock_quantity, NEW.stock_quantity)
                           ELSE '' END)
            WHEN TG_OP = 'DELETE' THEN format('Удален продукт: %s', OLD.name)
            END);

RETURN COALESCE(NEW, OLD);
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_audit_products
    AFTER INSERT OR UPDATE OR DELETE ON products
    FOR EACH ROW
    EXECUTE FUNCTION audit_products_changes();

-- Триггер для аудита изменений в таблице orders
CREATE OR REPLACE FUNCTION audit_orders_changes()
RETURNS TRIGGER AS $$
DECLARE
v_operation VARCHAR;
    v_user_id INTEGER;
BEGIN
    v_user_id := COALESCE(current_setting('app.user_id')::INTEGER, 0);

    IF TG_OP = 'INSERT' THEN
        v_operation := 'insert';
    ELSIF TG_OP = 'UPDATE' THEN
        v_operation := 'update';
    ELSIF TG_OP = 'DELETE' THEN
        v_operation := 'delete';
END IF;

INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, details)
VALUES ('order',
        COALESCE(NEW.order_id, OLD.order_id),
        v_operation,
        v_user_id,
        CASE
            WHEN TG_OP = 'INSERT' THEN format('Создан заказ для пользователя ID: %', NEW.user_id)
            WHEN TG_OP = 'UPDATE' THEN
                format('Обновлен заказ ID: %. Изменения: %s',
                       NEW.order_id,
                       CASE
                           WHEN OLD.status != NEW.status THEN
                               format('status: % -> %, ', OLD.status, NEW.status)
                           ELSE '' END ||
                       CASE
                           WHEN OLD.total_price != NEW.total_price THEN
                               format('total_price: % -> %', OLD.total_price, NEW.total_price)
                           ELSE '' END)
            WHEN TG_OP = 'DELETE' THEN format('Удален заказ ID: %', OLD.order_id)
            END);

RETURN COALESCE(NEW, OLD);
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_audit_orders
    AFTER INSERT OR UPDATE OR DELETE ON orders
    FOR EACH ROW
    EXECUTE FUNCTION audit_orders_changes();

-- Триггер для проверки достаточности товара на складе
CREATE OR REPLACE FUNCTION check_stock_before_order()
RETURNS TRIGGER AS $$
DECLARE
v_stock INTEGER;
    v_product_name VARCHAR;
BEGIN
    -- Получаем текущий запас товара
SELECT stock_quantity, name INTO v_stock, v_product_name
FROM products
WHERE product_id = NEW.product_id;

IF v_stock < NEW.quantity THEN
        RAISE EXCEPTION 'Недостаточно товара "%" на складе. Доступно: %, запрошено: %',
                        v_product_name, v_stock, NEW.quantity;
END IF;

RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_check_stock_before_order
    BEFORE INSERT OR UPDATE ON order_items
                         FOR EACH ROW
                         EXECUTE FUNCTION check_stock_before_order();

-- Триггер для автоматического уменьшения запаса при добавлении товара в заказ
CREATE OR REPLACE FUNCTION decrease_stock_on_order()
RETURNS TRIGGER AS $$
BEGIN
UPDATE products
SET stock_quantity = stock_quantity - NEW.quantity
WHERE product_id = NEW.product_id;

RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_decrease_stock_on_order
    AFTER INSERT ON order_items
    FOR EACH ROW
    EXECUTE FUNCTION decrease_stock_on_order();

-- Триггер для возврата товара на склад при удалении из заказа
CREATE OR REPLACE FUNCTION restore_stock_on_order_delete()
RETURNS TRIGGER AS $$
BEGIN
UPDATE products
SET stock_quantity = stock_quantity + OLD.quantity
WHERE product_id = OLD.product_id;

RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_restore_stock_on_order_delete
    AFTER DELETE ON order_items
    FOR EACH ROW
    EXECUTE FUNCTION restore_stock_on_order_delete();