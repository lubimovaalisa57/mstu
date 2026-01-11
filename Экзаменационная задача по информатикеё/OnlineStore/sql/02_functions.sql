-- Функция получения статуса заказа
CREATE OR REPLACE FUNCTION get_order_status(order_id_param INTEGER)
RETURNS VARCHAR AS $$
DECLARE
status_result VARCHAR;
BEGIN
SELECT status INTO status_result
FROM orders
WHERE order_id = order_id_param;

RETURN COALESCE(status_result, 'not_found');
END;
$$ LANGUAGE plpgsql;

-- Функция получения количества заказов пользователя
CREATE OR REPLACE FUNCTION get_user_order_count(user_id_param INTEGER)
RETURNS INTEGER AS $$
DECLARE
order_count INTEGER;
BEGIN
SELECT COUNT(*) INTO order_count
FROM orders
WHERE user_id = user_id_param;

RETURN COALESCE(order_count, 0);
END;
$$ LANGUAGE plpgsql;

-- Функция получения общей суммы потраченной пользователем
CREATE OR REPLACE FUNCTION get_total_spent_by_user(user_id_param INTEGER)
RETURNS DECIMAL AS $$
DECLARE
total_spent DECIMAL;
BEGIN
SELECT COALESCE(SUM(total_price), 0) INTO total_spent
FROM orders
WHERE user_id = user_id_param AND status = 'completed';

RETURN total_spent;
END;
$$ LANGUAGE plpgsql;

-- Функция проверки возможности возврата заказа
CREATE OR REPLACE FUNCTION can_return_order(order_id_param INTEGER)
RETURNS BOOLEAN AS $$
DECLARE
order_status VARCHAR;
    order_date TIMESTAMP;
    days_passed INTEGER;
BEGIN
SELECT status, order_date INTO order_status, order_date
FROM orders
WHERE order_id = order_id_param;

IF order_status != 'completed' THEN
        RETURN FALSE;
END IF;

    days_passed := EXTRACT(DAY FROM (CURRENT_TIMESTAMP - order_date));

RETURN days_passed <= 30;
END;
$$ LANGUAGE plpgsql;

-- Функция получения истории статусов заказа
CREATE OR REPLACE FUNCTION get_order_status_history(order_id_param INTEGER)
RETURNS TABLE(
    history_id INTEGER,
    old_status VARCHAR,
    new_status VARCHAR,
    changed_at TIMESTAMP,
    changed_by_name VARCHAR
) AS $$
BEGIN
RETURN QUERY
SELECT
    osh.history_id,
    osh.old_status,
    osh.new_status,
    osh.changed_at,
    u.name as changed_by_name
FROM order_status_history osh
         JOIN users u ON osh.changed_by = u.user_id
WHERE osh.order_id = order_id_param
ORDER BY osh.changed_at DESC;
END;
$$ LANGUAGE plpgsql;

-- Функция получения аудита по пользователю
CREATE OR REPLACE FUNCTION get_audit_log_by_user(user_id_param INTEGER)
RETURNS TABLE(
    log_id INTEGER,
    entity_type VARCHAR,
    entity_id INTEGER,
    operation VARCHAR,
    performed_at TIMESTAMP,
    performed_by_name VARCHAR,
    details TEXT
) AS $$
BEGIN
RETURN QUERY
SELECT
    al.log_id,
    al.entity_type,
    al.entity_id,
    al.operation,
    al.performed_at,
    u.name as performed_by_name,
    al.details
FROM audit_log al
         JOIN users u ON al.performed_by = u.user_id
WHERE al.performed_by = user_id_param
ORDER BY al.performed_at DESC;
END;
$$ LANGUAGE plpgsql;

-- Функция подсчета общей суммы заказов по статусу
CREATE OR REPLACE FUNCTION get_orders_sum_by_status(status_param VARCHAR)
RETURNS DECIMAL AS $$
DECLARE
total_sum DECIMAL;
BEGIN
SELECT COALESCE(SUM(total_price), 0) INTO total_sum
FROM orders
WHERE status = status_param;

RETURN total_sum;
END;
$$ LANGUAGE plpgsql;

-- Функция генерации отчета CSV
CREATE OR REPLACE FUNCTION generate_order_history_report()
RETURNS TABLE(
    order_id INTEGER,
    customer_name VARCHAR,
    current_status VARCHAR,
    old_status VARCHAR,
    new_status VARCHAR,
    status_changed_at TIMESTAMP,
    operation_type VARCHAR,
    performed_by VARCHAR,
    performed_at TIMESTAMP
) AS $$
BEGIN
RETURN QUERY
SELECT
    o.order_id,
    u_customer.name as customer_name,
    o.status as current_status,
    osh.old_status,
    osh.new_status,
    osh.changed_at as status_changed_at,
    al.operation as operation_type,
    u_performer.name as performed_by,
    al.performed_at
FROM orders o
         JOIN users u_customer ON o.user_id = u_customer.user_id
         LEFT JOIN order_status_history osh ON o.order_id = osh.order_id
         LEFT JOIN audit_log al ON o.order_id = al.entity_id AND al.entity_type = 'order'
         LEFT JOIN users u_performer ON al.performed_by = u_performer.user_id
ORDER BY o.order_id, osh.changed_at DESC, al.performed_at DESC;
END;
$$ LANGUAGE plpgsql;