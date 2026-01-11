-- Удаляем все таблицы в правильном порядке (из-за foreign keys)
-- Сначала удаляем таблицы, которые зависят от других
DROP TABLE IF EXISTS payments CASCADE;
DROP TABLE IF EXISTS order_status_history CASCADE;
DROP TABLE IF EXISTS order_items CASCADE;
DROP TABLE IF EXISTS audit_log CASCADE;  -- Перемещено выше, т.к. зависит от users
DROP TABLE IF EXISTS orders CASCADE;
DROP TABLE IF EXISTS products CASCADE;
DROP TABLE IF EXISTS users CASCADE;

-- Теперь создаем таблицы заново
-- Таблица пользователей (создаём первой, т.к. на неё ссылаются другие таблицы)
CREATE TABLE IF NOT EXISTS users (
                                     user_id SERIAL PRIMARY KEY,
                                     name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    role VARCHAR(20) NOT NULL CHECK (role IN ('admin', 'manager', 'customer')),
    password_hash VARCHAR(255),
    loyalty_level INTEGER DEFAULT 0 CHECK (loyalty_level IN (0, 1))
    );

-- Таблица продуктов (не зависит от других, создаём второй)
CREATE TABLE IF NOT EXISTS products (
                                        product_id SERIAL PRIMARY KEY,
                                        name VARCHAR(100) NOT NULL,
    price DECIMAL(10,2) NOT NULL CHECK (price > 0),
    stock_quantity INTEGER NOT NULL CHECK (stock_quantity >= 0),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    );

-- Таблица заказов (зависит от users)
CREATE TABLE IF NOT EXISTS orders (
                                      order_id SERIAL PRIMARY KEY,
                                      user_id INTEGER NOT NULL REFERENCES users(user_id),
    status VARCHAR(20) NOT NULL DEFAULT 'pending'
    CHECK (status IN ('pending', 'processing', 'completed', 'canceled', 'returned')),
    total_price DECIMAL(10,2) DEFAULT 0,
    order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    );

-- Таблица элементов заказа (зависит от orders и products)
CREATE TABLE IF NOT EXISTS order_items (
                                           order_item_id SERIAL PRIMARY KEY,
                                           order_id INTEGER NOT NULL REFERENCES orders(order_id) ON DELETE CASCADE,
    product_id INTEGER NOT NULL REFERENCES products(product_id),
    quantity INTEGER NOT NULL CHECK (quantity > 0),
    price DECIMAL(10,2) NOT NULL,
    UNIQUE(order_id, product_id)
    );

-- Таблица истории статусов (зависит от orders и users)
CREATE TABLE IF NOT EXISTS order_status_history (
                                                    history_id SERIAL PRIMARY KEY,
                                                    order_id INTEGER NOT NULL REFERENCES orders(order_id),
    old_status VARCHAR(20),
    new_status VARCHAR(20) NOT NULL,
    changed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    changed_by INTEGER NOT NULL REFERENCES users(user_id)
    );

-- Таблица аудита (зависит от users)
CREATE TABLE IF NOT EXISTS audit_log (
                                         log_id SERIAL PRIMARY KEY,
                                         entity_type VARCHAR(20) NOT NULL CHECK (entity_type IN ('order', 'product', 'user')),
    entity_id INTEGER NOT NULL,
    operation VARCHAR(20) NOT NULL CHECK (operation IN ('insert', 'update', 'delete', 'select', 'create', 'approve', 'cancel', 'return', 'payment')),
    performed_by INTEGER NOT NULL REFERENCES users(user_id),
    performed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    details TEXT
    );

-- Таблица платежей (зависит от orders)
CREATE TABLE IF NOT EXISTS payments (
                                        payment_id SERIAL PRIMARY KEY,
                                        order_id INTEGER NOT NULL REFERENCES orders(order_id),
    amount DECIMAL(10,2) NOT NULL,
    payment_method VARCHAR(50) NOT NULL,
    payment_status VARCHAR(20) DEFAULT 'pending'
    CHECK (payment_status IN ('pending', 'completed', 'failed', 'refunded')),
    payment_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    transaction_id VARCHAR(100)
    );

-- Индексы для оптимизации
CREATE INDEX IF NOT EXISTS idx_orders_user_id ON orders(user_id);
CREATE INDEX IF NOT EXISTS idx_orders_status ON orders(status);
CREATE INDEX IF NOT EXISTS idx_order_items_order_id ON order_items(order_id);
CREATE INDEX IF NOT EXISTS idx_order_status_history_order_id ON order_status_history(order_id);
CREATE INDEX IF NOT EXISTS idx_audit_log_performed_by ON audit_log(performed_by);
CREATE INDEX IF NOT EXISTS idx_audit_log_entity ON audit_log(entity_type, entity_id);

-- Добавляем тестовые данные
INSERT INTO users (name, email, role, loyalty_level) VALUES
                                                         ('Администратор', 'admin@store.com', 'admin', 1),
                                                         ('Менеджер', 'manager@store.com', 'manager', 1),
                                                         ('Покупатель', 'customer@store.com', 'customer', 0)
    ON CONFLICT (email) DO NOTHING;

INSERT INTO products (name, price, stock_quantity) VALUES
                                                       ('Ноутбук Lenovo', 45000.00, 10),
                                                       ('Смартфон Samsung', 35000.00, 15),
                                                       ('Наушники Sony', 8000.00, 20),
                                                       ('Клавиатура Logitech', 3000.00, 30),
                                                       ('Мышь беспроводная', 1500.00, 40)
    ON CONFLICT DO NOTHING;

-- Проверяем создание
SELECT 'Таблицы созданы' as status;
SELECT COUNT(*) as users_count FROM users;
SELECT COUNT(*) as products_count FROM products;