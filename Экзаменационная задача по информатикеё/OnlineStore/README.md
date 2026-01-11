1. Описание задачи

ЦЕЛЬ РАБОТЫ:
Создание системы интернет-магазина с использованием принципов объектно-ориентированного программирования, умных указателей и работы с PostgreSQL.

КРАТКОЕ ОПИСАНИЕ СИСТЕМЫ:
Система реализует интернет-магазин с тремя типами пользователей (администратор, менеджер, покупатель), управлением товарами, обработкой заказов, системой оплаты, аудитом действий и генерацией отчетов.

ИСПОЛЬЗУЕМЫЕ ТЕХНОЛОГИИ:

- Язык программирования: C++17
- База данных: PostgreSQL
- Библиотека для работы с БД: libpqxx

2. Архитектура проекта

КЛАССЫ И ИХ ВЗАИМОСЯЗИ

User (абстрактный)
├── Admin
├── Manager
└── Customer

DatabaseConnection<T> (шаблонный)
Order ──┐
├── OrderItem
└── Payment
└── PaymentStrategy (абстрактный)
├── CreditCardPayment
├── EWalletPayment
└── SBPPayment

ПРИМЕНЕНИЕ ПРИНЦИПОВ ООП

1.Наследование:

- Абстрактный класс `User` с чисто виртуальными методами `showMenu()` и `performAction()`
- Производные классы `Admin`, `Manager`, `Customer` переопределяют виртуальные методы
- Стратегия оплаты: `PaymentStrategy` → `CreditCardPayment`, `EWalletPayment`, `SBPPayment`

  2.Полиморфизм:
  // Пример полиморфного вызова
  std::shared_ptr<User> user = std::make_shared<Admin>(...);
  user->showMenu(); // Вызывается Admin::showMenu()
  user->performAction(choice); // Динамическое связывание

  3.Композиция:
  // Класс Order владеет OrderItem и Payment
  class Order {
  private:
  std::vector<std::shared_ptr<OrderItem>> items; // Композиция
  std::unique_ptr<Payment> payment; // Композиция
  };

  4.Агрегация:
  // Класс User агрегирует заказы
  class User {
  protected:
  std::vector<std::shared_ptr<Order>> orders; // Агрегация
  };

ШАБЛОННЫЙ КЛАСС DatabaseConnection<T>

template<typename T>
class DatabaseConnection {
private:
std::unique_ptr<pqxx::connection> conn; // Умный указатель для управления ресурсами
public:
// Конструктор с подключением к БД
DatabaseConnection(const std::string& connection_string);

    // Основные методы работы с БД
    std::vector<std::vector<std::string>> executeQuery(const std::string& query);
    void executeNonQuery(const std::string& query);
    void beginTransaction();
    void commitTransaction();
    void rollbackTransaction();
    bool isConnected() const;

    ~DatabaseConnection();  // Автоматическое закрытие соединения

};

3. Работа с базой данных

СТРУКТУРА БАЗЫ ДАННЫХ
-таблицы
-функции
-процедуры
-триггеры
-индексы
-тестовые данные

ТАБЛИЦЫ:
1.users - пользователи системы
2.products - каталог товаров
3.orders - заказы
4.rder_items - товары в заказах
5.order_status_history - история изменений статусов
6.audit_log - журнал аудита действий
7.payments - платежи

ХРАНИМЫЕ ПРОЦЕДЦРЫ И ФУНКЦИИ

Основные функции:
-- Получение статуса заказа
CREATE OR REPLACE FUNCTION get_order_status(order_id_param INTEGER)

-- Количество заказов пользователя
CREATE OR REPLACE FUNCTION get_user_order_count(user_id_param INTEGER)

-- Общая сумма потраченная пользователем
CREATE OR REPLACE FUNCTION get_total_spent_by_user(user_id_param INTEGER)

-- Проверка возможности возврата заказа
CREATE OR REPLACE FUNCTION can_return_order(order_id_param INTEGER)

-- История статусов заказа
CREATE OR REPLACE FUNCTION get_order_status_history(order_id_param INTEGER)

-- Журнал аудита по пользователю
CREATE OR REPLACE FUNCTION get_audit_log_by_user(user_id_param INTEGER)

Основные процедуры:
-- Создание пустого заказа
CREATE OR REPLACE PROCEDURE create_empty_order(p_user_id INTEGER, OUT p_order_id INTEGER)

-- Добавление товара в заказ
CREATE OR REPLACE PROCEDURE add_product_to_order(p_order_id INTEGER, p_product_id INTEGER, p_quantity INTEGER, p_user_id INTEGER)

-- Утверждение заказа менеджером
CREATE OR REPLACE PROCEDURE approve_order(p_order_id INTEGER, p_manager_id INTEGER)

-- Обновление статуса заказа
CREATE OR REPLACE PROCEDURE update_order_status(p_order_id INTEGER, p_new_status VARCHAR, p_changed_by INTEGER)

-- Обработка возврата заказа
CREATE OR REPLACE PROCEDURE process_order_return(p_order_id INTEGER, p_customer_id INTEGER)

Основные триггеры:
-- 1. Автоматическое обновление updated_at при изменении заказа
CREATE TRIGGER trg_orders_update_timestamp

-- 2. Логирование изменений статусов заказов
CREATE TRIGGER trg_order_status_change

-- 3. Обновление цен в заказах при изменении цены продукта
CREATE TRIGGER trg_update_order_prices

-- 4. Аудит изменений в таблицах products и orders
CREATE TRIGGER trg_audit_products
CREATE TRIGGER trg_audit_orders

-- 5. Проверка достаточности товара на складе
CREATE TRIGGER trg_check_stock_before_order

-- 6. Автоматическое управление запасами
CREATE TRIGGER trg_decrease_stock_on_order
CREATE TRIGGER trg_restore_stock_on_order_delete

МЕХАНИЗМ ТРАНЗАКЦИЙ И ОТКАТА ПРИ ОШИБКАХ

// Пример использования транзакций в C++
db->beginTransaction();
try {
db->executeNonQuery("UPDATE products SET stock_quantity = stock_quantity - 1 WHERE product_id = 5");
db->executeNonQuery("INSERT INTO order_items (order_id, product_id, quantity) VALUES (100, 5, 1)");
db->commitTransaction();
std::cout << "Транзакция успешно завершена" << std::endl;
} catch (const std::exception& e) {
db->rollbackTransaction();
logAudit("order", 100, "error");
std::cerr << "Ошибка транзакции: " << e.what() << std::endl;
}

4. Умные указатели и STL

ИСПОЛЬЗОВАНИЕ std::unique_ptr и std::shared_ptr

- std::shared_ptr для совместного владения:
  // Создание пользователей с shared_ptr
  std::shared_ptr<User> admin = std::make_shared<Admin>(1, "Администратор", "admin@store.com", db);
  std::shared_ptr<User> customer = std::make_shared<Customer>(3, "Покупатель", "customer@store.com", db);

// Агрегация заказов в User
class User {
protected:
std::vector<std::shared_ptr<Order>> orders; // shared_ptr для разделяемого владения
};

- std::unique_ptr для эксклюзивного владения:
  // Композиция Payment в Order
  class Order {
  private:
  std::unique_ptr<Payment> payment; // unique_ptr для исключительного владения

public:
void setPayment(std::unique_ptr<Payment> pay) {
payment = std::move(pay); // Перемещение владения
}
};

// Использование
auto payment = std::make_unique<Payment>(order_id, amount);
order->setPayment(std::move(payment)); // Владение передается Order

ПРИМЕРЫ ИСПОЛЬЗОВАНИЯ

- std::find_if с лямбда-выражением:
  void Order::removeItem(int product_id) {
  auto it = std::find_if(items.begin(), items.end(),
  [product_id](const auto& item) { // Лямбда-выражение
  return item->getProductId() == product_id;
  });

      if (it != items.end()) {
          total_price -= (*it)->getTotalPrice();
          items.erase(it);
      }

  }

- std::accumulate с лямбда-выражением:
  int Order::getItemCount() const {
  return std::accumulate(items.begin(), items.end(), 0,
  [](int sum, const auto& item) { // Лямбда для агрегации
  return sum + item->getQuantity();
  });
  }

- std::copy_if для фильтрации:
  // Пример фильтрации заказов по статусу
  std::vector<std::shared_ptr<Order>> filterOrdersByStatus(
  const std::vector<std::shared_ptr<Order>>& orders,
  const std::string& status) {

      std::vector<std::shared_ptr<Order>> filtered;
      std::copy_if(orders.begin(), orders.end(), std::back_inserter(filtered),
          [&status](const auto& order) {  // Захват status по ссылке
              return order->getStatus() == status;
          });
      return filtered;

  }

- Лямбда-выражения для проверки прав доступа:
  // Пример проверки прав пользователя
  auto hasPermission = [](const User& user, const std::string& requiredRole) {
  return user.getRole() == requiredRole || user.getRole() == "admin";
  };
  if (hasPermission(\*currentUser, "manager")) {
  // Выполнить действие, доступное менеджеру
  }

5. Логика ролей и прав доступа

ВОЗМОЖНОСТИ РОЛЕЙ

Администратор:

- Полный доступ ко всем функциям системы
- Управление продуктами (добавление, обновление, удаление)
- Просмотр и изменение любых заказов
- Доступ к журналу аудита и истории изменений
- Генерация отчетов

Менеджер:

- Утверждение заказов от покупателей
- Обновление информации о товарах на складе
- Изменение статусов заказов в рамках полномочий
- Доступ к истории утвержденных заказов

Покупатель:

- Создание новых заказов
- Добавление/удаление товаров в заказе
- Просмотр статусов и списка своих заказов
- Оплата заказов через различные методы
- Оформление возвратов (при соблюдении условий)

ОГРАНИЧЕНИЯ ДОСТУПА

// Пример проверки доступа к истории заказов
void User::viewOrderStatusHistory(int order_id) {
if (role == "customer") {
// Покупатель может видеть только свои заказы
std::string checkQuery = "SELECT user_id FROM orders WHERE order_id = " +
std::to_string(order_id);
auto result = db->executeQuery(checkQuery);

        if (!result.empty() && std::stoi(result[0][0]) != user_id) {
            std::cout << "Доступ запрещен: вы можете просматривать только свои заказы\n";
            return;
        }
    }
    // ... выполнение запроса

}

Ограничения журнала аудита:

- Администратор: полный доступ ко всем записям
- Менеджер: только записи, связанные с заказами
- Покупатель: доступ запрещен

6. Аудит и история изменений

Таблицы аудита

ОПИСАНИЕ ТАБЛИЦ

- order_status_history:
  CREATE TABLE order_status_history (
  history_id SERIAL PRIMARY KEY,
  order_id INTEGER NOT NULL REFERENCES orders(order_id),
  old_status VARCHAR(20),
  new_status VARCHAR(20) NOT NULL,
  changed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  changed_by INTEGER NOT NULL REFERENCES users(user_id)
  );
- audit_log:
  CREATE TABLE audit_log (
  log_id SERIAL PRIMARY KEY,
  entity_type VARCHAR(20) NOT NULL CHECK (entity_type IN ('order', 'product', 'user')),
  entity_id INTEGER NOT NULL,
  operation VARCHAR(20) NOT NULL CHECK (operation IN ('insert', 'update', 'delete', ...)),
  performed_by INTEGER NOT NULL REFERENCES users(user_id),
  performed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  details TEXT
  );

МЕХАНИЗМ АВТОМАТИЧЕСКОГО ЛОГИРОВАНИЯ

- Триггер для аудита продуктов:
  CREATE TRIGGER trg_audit_products
  AFTER INSERT OR UPDATE OR DELETE ON products
  FOR EACH ROW
  EXECUTE FUNCTION audit_products_changes();

- Функция аудита:
  CREATE OR REPLACE FUNCTION audit_products_changes()
  RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, details)
    VALUES ('product', COALESCE(NEW.product_id, OLD.product_id),
            TG_OP,  -- 'INSERT', 'UPDATE', 'DELETE'
            COALESCE(current_setting('app.user_id')::INTEGER, 0),
            format('Изменен продукт: %s', COALESCE(NEW.name, OLD.name)));
    RETURN COALESCE(NEW, OLD);
END;
$$ LANGUAGE plpgsql;

ПРИМЕРЫ ЗАПИСЕЙ АУДИТА

- В таблице audit_log:

log_id | entity_type | entity_id | operation | performed_by | performed_at | details
-------+-------------+-----------+-----------+--------------+------------------------+--------------------------------------------------------
1 | product | 1 | insert | 1 | 2026-01-09 12:30:45 | Создан продукт: Ноутбук Lenovo, цена: 45000
2 | order | 4 | update | 2 | 2026-01-09 13:49:00 | Статус изменен: pending -> processing
3 | order | 3 | payment | 3 | 2026-01-09 12:53:25 | Оплата заказа через банковскую карту

- В таблице order_status_history:

history_id | order_id | old_status | new_status | changed_at | changed_by
-----------+----------+------------+------------+----------------------+------------
1 | 4 | pending | processing | 2026-01-09 13:49:00 | 2
2 | 2 | processing | canceled | 2026-01-09 15:00:36 | 3

7. Отчёт в формате CSV

ОПИСАНИЕ ОТЧЕТА

Отчёт «История изменений заказов и действий пользователей» объединяет данные из таблиц `orders`, `order_status_history` и `audit_log`, предоставляя полную картину жизненного цикла заказов.

SQL-ЗАПРОС ДЛЯ ФОРМИРОВАНИЯ ОТЧЕТА

-- Из функции generate_order_history_report() в 02_functions.sql
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

РЕАЛИЗАЦИЯ В C++

void Admin::generateReportCSV() {
std::string report*query = R"(
SELECT
o.order_id::TEXT,
u.name,
o.status,
o.total_price::TEXT,
TO_CHAR(o.order_date, 'YYYY-MM-DD HH24:MI:SS'),
COALESCE(
(SELECT TO_CHAR(changed_at, 'YYYY-MM-DD HH24:MI:SS')
FROM order_status_history
WHERE order_id = o.order_id
ORDER BY changed_at DESC LIMIT 1),
'Нет данных'
),
(
SELECT COUNT(*)::TEXT
FROM order*status_history
WHERE order_id = o.order_id
),
COALESCE(
(SELECT operation
FROM audit_log
WHERE entity_type = 'order' AND entity_id = o.order_id
ORDER BY performed_at DESC LIMIT 1),
'Нет операций'
),
COALESCE(
(SELECT TO_CHAR(performed_at, 'YYYY-MM-DD HH24:MI:SS')
FROM audit_log
WHERE entity_type = 'order' AND entity_id = o.order_id
ORDER BY performed_at DESC LIMIT 1),
'Нет данных'
),
(
SELECT COUNT(*)::TEXT
FROM audit_log
WHERE entity_type = 'order' AND entity_id = o.order_id
)
FROM orders o
JOIN users u ON o.user_id = u.user_id
ORDER BY o.order_date DESC
)";
// ... создание CSV файла
}

ПРИМЕР СОДЕРЖИМОГО CSV-файла

ID заказа;Покупатель;Статус заказа;Сумма заказа;Дата заказа;Последнее изменение статуса;Кол-во изменений статуса;Последняя операция аудита;Время последнего аудита;Всего записей аудита
4;Покупатель;processing;45000.00;2026-01-09 13:45:12;2026-01-09 13:49:00;1;approve;2026-01-09 13:49:00;3
3;Покупатель;processing;3004.00;2026-01-09 12:52:29;Нет данных;0;payment;2026-01-09 12:53:25;4
2;Покупатель;canceled;35000.00;2026-01-09 12:50:16;2026-01-09 15:00:36;1;update;2026-01-09 15:00:36;4
1;Покупатель;processing;0.00;2026-01-09 12:47:59;Нет данных;0;create;2026-01-09 12:47:59;1

8. Сборка и запуск проекта

ТРЕБОВАНИЯ К ОКРУЖЕНИЮ

- Компилятор C++: g++ 9.0+ или clang 10.0+ с поддержкой C++17
- PostgreSQL: версия 12+
- libpqxx: версия 7.0+
- CMake: версия 3.15+

УСТАНОВКА ЗАВИСИМОСТЕЙ

macOS (Homebrew):
brew install postgresql@14
brew install libpqxx
brew install cmake

СБОРКА ПРОЕКТА

1.Клонирование репозитория:
git clone <repository-url>
cd online-store

2.Создание базы данных:
sudo service postgresql start # или brew services start postgresql@14
sudo -u postgres psql -c "CREATE DATABASE online_store;"
sudo -u postgres psql -c "CREATE USER store_user WITH PASSWORD 'password';"
sudo -u postgres psql -c "GRANT ALL PRIVILEGES ON DATABASE online_store TO store_user;"
psql -h localhost -U store_user -d online_store -f sql/01_tables.sql
psql -h localhost -U store_user -d online_store -f sql/02_functions.sql
psql -h localhost -U store_user -d online_store -f sql/03_procedures.sql
psql -h localhost -U store_user -d online_store -f sql/04_triggers.sql

3.Сборка проекта с CMake:
mkdir build && cd build
cmake ..
make
./online_store

ПРИМЕР РАБОТЫ ПРОГРАММЫ

=== ИНТЕРНЕТ-МАГАЗИН ===
Подключено к базе данных
Выберите роль:

1. Администратор
2. Менеджер
3. Покупатель
4. Выход
   Выбор: 1
   Добро пожаловать, Администратор!

=== Меню администратора ===

1. Добавить новый продукт
2. Обновить информацию о продукте
3. Удалить продукт
4. Просмотр всех заказов
5. Просмотр деталей заказа
6. Изменить статус заказа
7. Просмотр истории статусов заказа
8. Просмотр журнала аудита
9. Сформировать отчёт (CSV)
10. Выход
    Выбор: 4

=== Просмотр всех заказов ===
ID Покупатель Статус Сумма Дата заказа Товаров

---

4 Покупатель processing 45000.00 2026-01-09 2
3 Покупатель processing 3004.00 2026-01-09 2
2 Покупатель canceled 35000.00 2026-01-09 1
1 Покупатель processing 0.00 2026-01-09 0

ПРИМЕРЫ РАБОТЫ МЕНЮ ДЛЯ РАЗНЫХ РОЛЕЙ

- Меню менеджера:

=== Меню менеджера ===

1. Просмотр заказов в ожидании утверждения
2. Утвердить заказ
3. Обновить количество товара на складе
4. Просмотр деталей заказа
5. Изменить статус заказа (в рамках полномочий)
6. Просмотр истории утверждённых заказов
7. Просмотр истории статусов заказов
8. Выход

- Меню покупателя:

=== Меню покупателя ===

1. Создать новый заказ
2. Добавить товар в заказ
3. Удалить товар из заказа
4. Просмотр моих заказов
5. Просмотр статуса заказа
6. Оплатить заказ
7. Оформить возврат заказа
8. Просмотр истории статусов заказа
9. Выход

ПРИМЕРЫ ЛОГОВ И ИСТОРИИ ИЗМЕНЕНИЯ ЗАКАЗОВ

- Аудит действий:

=== Журнал аудита ===
ID Тип Объект Операция Выполнил Время Детали

---

15 order 4 update Менеджер 2026-01-09 13:49:00 Заказ утвержден менеджером...
12 product 3 update Администратор 2026-01-09 12:40:15 Обновлен продукт: Наушники...
8 order 3 payment Покупатель 2026-01-09 12:53:25 Оплата заказа через банков...

- История статусов заказа:

=== История статусов заказа ID: 4 ===
ID Старый статус Новый статус Дата изменения Кем изменен

---

1 pending processing 2026-01-09 13:49:00 Менеджер

СТРУКТУРА ПРОЕКТА

OnlineStore/
├── CMakeLists.txt # Файл конфигурации сборки
├── README.md # Основная документация
├── include/ # Заголовочные файлы
│ ├── User.h
│ ├── Admin.h
│ ├── Manager.h
│ ├── Customer.h
│ ├── DatabaseConnection.h
│ ├── Order.h
│ ├── OrderItem.h
│ ├── Payment.h
│ └── PaymentStrategy.h
├── src/ # Исходные файлы
│ ├── main.cpp
│ ├── User.cpp
│ ├── Admin.cpp
│ ├── Manager.cpp
│ ├── Customer.cpp
│ └── PaymentStrategy.cpp
├── sql/ # SQL-скрипты
│ ├── 01_tables.sql # Создание таблиц
│ ├── 02_functions.sql # Функции PostgreSQL
│ ├── 03_procedures.sql # Хранимые процедуры
│ ├── 04_triggers.sql # Триггеры
│ └── 05_sample_data.sql # Тестовые данные
└── reports/ # Генерируемые отчёты
└── audit_report.csv # Пример CSV-отчёта
