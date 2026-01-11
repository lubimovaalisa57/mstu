#include "../include/Manager.h"
#include <iostream>
#include <iomanip>
#include <limits>

Manager::Manager(int id, std::string n, std::string e,
                 std::shared_ptr<DatabaseConnection<std::string>> database)
    : User(id, std::move(n), std::move(e), "manager", database) {}

void Manager::showMenu() {
    std::cout << "\nМеню менеджера:\n";
    std::cout << "1. Просмотр заказов в ожидании утверждения\n";
    std::cout << "2. Утвердить заказ\n";
    std::cout << "3. Обновить количество товара на складе\n";
    std::cout << "4. Просмотр деталей заказа\n";
    std::cout << "5. Изменить статус заказа (в рамках полномочий)\n";
    std::cout << "6. Просмотр истории утверждённых заказов\n";
    std::cout << "7. Просмотр истории статусов заказов\n";
    std::cout << "8. Выход\n";
    std::cout << "Выбор: ";
}

void Manager::performAction(int choice) {
    switch(choice) {
        case 1: viewPendingOrders(); break;
        case 2: approveOrder(); break;
        case 3: updateStock(); break;
        case 4: viewOrderDetails(); break;
        case 5: changeOrderStatus(); break;
        case 6: viewMyApprovedOrders(); break;
        case 7: viewStatusHistory(); break;
        case 8:
            std::cout << "Выход из программы...\n";
            exit(0); // Выход из программы
            break;
        default:
            std::cout << "Неверный выбор\n";
    }
}

void Manager::viewPendingOrders() {
    std::cout << "\n=== Заказы в ожидании утверждения ===\n";

    std::string query = R"(
        SELECT o.order_id, u.name as customer_name,
               o.total_price, o.order_date,
               COUNT(oi.order_item_id) as items_count
        FROM orders o
        JOIN users u ON o.user_id = u.user_id
        LEFT JOIN order_items oi ON o.order_id = oi.order_id
        WHERE o.status = 'pending'
        GROUP BY o.order_id, u.name, o.total_price, o.order_date
        ORDER BY o.order_date ASC
    )";

    auto result = db->executeQuery(query);

    if (result.empty()) {
        std::cout << "Нет заказов на утверждение\n";
        return;
    }

    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(20) << "Покупатель"
              << std::setw(12) << "Сумма"
              << std::setw(15) << "Дата заказа"
              << std::setw(10) << "Товаров"
              << "\n";
    std::cout << std::string(75, '-') << "\n";

    for (const auto& row : result) {
        std::cout << std::left
                  << std::setw(8) << row[0]
                  << std::setw(20) << (row[1].length() > 18 ? row[1].substr(0, 15) + "..." : row[1])
                  << std::setw(12) << row[2]
                  << std::setw(15) << row[3].substr(0, 10)
                  << std::setw(10) << row[4]
                  << "\n";
    }
}
//здесь я исправил на processing
void Manager::approveOrder() {
    std::cout << "\n=== Утверждение заказа ===\n";

    // Сначала показываем заказы на утверждение
    viewPendingOrders();

    if (db->executeQuery("SELECT order_id FROM orders WHERE status = 'pending'").empty()) {
        return;
    }

    std::cout << "Введите ID заказа для утверждения: ";
    int order_id;
    std::cin >> order_id;

    // Очищаем буфер ввода
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Вы уверены, что хотите утвердить заказ #" << order_id << "? (да/нет): ";
    std::string confirm;
    std::getline(std::cin, confirm);

    if (confirm != "да" && confirm != "д" && confirm != "yes" && confirm != "y") {
        std::cout << "Операция отменена\n";
        return;
    }

    try {
        // Используем хранимую процедуру для утверждения заказа
        std::string call_proc = "CALL approve_order(" +
                               std::to_string(order_id) + ", " +
                               std::to_string(user_id) + ")";

        db->beginTransaction();
        db->executeNonQuery(call_proc);
        db->commitTransaction();

        std::cout << "Заказ #" << order_id << " успешно утвержден\n";

        // Автоматическое логирование выполняется в триггере

    } catch (const std::exception& e) {
        db->rollbackTransaction();
        std::cerr << "Ошибка при утверждении заказа: " << e.what() << std::endl;
        std::cout << "Возможно, заказ уже обработан или не существует\n";
    }
}

void Manager::updateStock() {
    std::cout << "\n=== Обновление количества товара на складе ===\n";

    // Показываем текущий склад
    std::string query = R"(
        SELECT product_id, name, price, stock_quantity,
               CASE
                   WHEN stock_quantity <= 5 THEN 'НИЗКИЙ'
                   WHEN stock_quantity <= 20 THEN 'СРЕДНИЙ'
                   ELSE 'НОРМА'
               END as stock_level
        FROM products
        ORDER BY stock_quantity ASC, name ASC
    )";

    auto products = db->executeQuery(query);

    if (products.empty()) {
        std::cout << "Продуктов нет в базе данных\n";
        return;
    }

    std::cout << std::left
              << std::setw(6) << "ID"
              << std::setw(25) << "Название товара"
              << std::setw(10) << "Цена"
              << std::setw(12) << "Количество"
              << std::setw(10) << "Статус"
              << "\n";
    std::cout << std::string(63, '-') << "\n";

    for (const auto& product : products) {
        std::cout << std::left
                  << std::setw(6) << product[0]
                  << std::setw(25) << (product[1].length() > 23 ? product[1].substr(0, 20) + "..." : product[1])
                  << std::setw(10) << product[2]
                  << std::setw(12) << product[3]
                  << std::setw(10) << product[4]
                  << "\n";
    }

    std::cout << "\nВведите ID продукта для обновления (0 для отмены): ";
    int product_id;
    std::cin >> product_id;

    if (product_id == 0) {
        std::cout << "Операция отменена\n";
        return;
    }

    // Проверяем существование продукта
    std::string check_query = "SELECT name FROM products WHERE product_id = " +
                             std::to_string(product_id);
    auto check_result = db->executeQuery(check_query);

    if (check_result.empty()) {
        std::cout << "Продукт с ID " << product_id << " не найден\n";
        return;
    }

    std::string product_name = check_result[0][0];
    std::cout << "Выбран товар: " << product_name << "\n";

    std::cout << "Введите новое количество: ";
    int quantity;
    std::cin >> quantity;

    if (quantity < 0) {
        std::cout << "Количество не может быть отрицательным\n";
        return;
    }

    std::cout << "Причина изменения (опционально): ";
    std::cin.ignore();
    std::string reason;
    std::getline(std::cin, reason);

    std::string update_query = "UPDATE products SET stock_quantity = " +
                              std::to_string(quantity) +
                              " WHERE product_id = " + std::to_string(product_id);

    try {
        db->beginTransaction();
        db->executeNonQuery(update_query);

        // Логируем в audit_log с деталями
        std::string audit_query = "INSERT INTO audit_log (entity_type, entity_id, operation, performed_by, details) "
                                 "VALUES ('product', " + std::to_string(product_id) +
                                 ", 'update', " + std::to_string(user_id) +
                                 ", 'Обновление склада: " + reason +
                                 " (новое количество: " + std::to_string(quantity) + ")')";
        db->executeNonQuery(audit_query);

        db->commitTransaction();
        std::cout << "Количество товара '" << product_name << "' обновлено до " << quantity << " единиц\n";

    } catch (const std::exception& e) {
        db->rollbackTransaction();
        std::cerr << "Ошибка при обновлении склада: " << e.what() << std::endl;
    }
}

void Manager::viewOrderDetails() {
    std::cout << "\n=== Просмотр деталей заказа ===\n";

    std::cout << "Введите ID заказа: ";
    int order_id;
    std::cin >> order_id;

    // Получаем основную информацию о заказе
    std::string order_query = R"(
        SELECT o.order_id, u.name as customer_name, u.email,
               o.status, o.total_price, o.order_date, o.updated_at,
               (SELECT name FROM users WHERE user_id =
                   (SELECT performed_by FROM audit_log
                    WHERE entity_type = 'order' AND entity_id = o.order_id
                    AND operation = 'approve' LIMIT 1)
               ) as approved_by
        FROM orders o
        JOIN users u ON o.user_id = u.user_id
        WHERE o.order_id = )" + std::to_string(order_id);

    auto order_result = db->executeQuery(order_query);

    if (order_result.empty()) {
        std::cout << "Заказ #" << order_id << " не найден\n";
        return;
    }

    auto order = order_result[0];

    std::cout << "\n=== Информация о заказе #" << order_id << " ===\n";
    std::cout << "Покупатель: " << order[1] << " (" << order[2] << ")\n";
    std::cout << "Статус: " << order[3] << "\n";
    std::cout << "Общая сумма: " << order[4] << " руб.\n";
    std::cout << "Дата заказа: " << order[5] << "\n";
    std::cout << "Последнее обновление: " << order[6] << "\n";
    if (!order[7].empty()) {
        std::cout << "Утвержден менеджером: " << order[7] << "\n";
    }

    // Получаем товары в заказе
    std::string items_query = R"(
        SELECT p.name, oi.quantity, oi.price, (oi.quantity * oi.price) as total
        FROM order_items oi
        JOIN products p ON oi.product_id = p.product_id
        WHERE oi.order_id = )" + std::to_string(order_id) +
        " ORDER BY oi.order_item_id";

    auto items_result = db->executeQuery(items_query);

    if (!items_result.empty()) {
        std::cout << "\nТовары в заказе:\n";
        std::cout << std::left
                  << std::setw(30) << "Название"
                  << std::setw(10) << "Кол-во"
                  << std::setw(12) << "Цена"
                  << std::setw(12) << "Сумма"
                  << "\n";
        std::cout << std::string(64, '-') << "\n";

        for (const auto& item : items_result) {
            std::cout << std::left
                      << std::setw(30) << (item[0].length() > 28 ? item[0].substr(0, 25) + "..." : item[0])
                      << std::setw(10) << item[1]
                      << std::setw(12) << item[2]
                      << std::setw(12) << item[3]
                      << "\n";
        }
    }

    // Получаем историю статусов для этого заказа
    std::string history_query = R"(
        SELECT old_status, new_status, changed_at,
               (SELECT name FROM users WHERE user_id = changed_by) as changed_by_name
        FROM order_status_history
        WHERE order_id = )" + std::to_string(order_id) +
        " ORDER BY changed_at DESC";

    auto history_result = db->executeQuery(history_query);

    if (!history_result.empty()) {
        std::cout << "\nИстория изменений статуса:\n";
        std::cout << std::left
                  << std::setw(15) << "Старый статус"
                  << std::setw(15) << "Новый статус"
                  << std::setw(20) << "Дата изменения"
                  << std::setw(15) << "Изменен"
                  << "\n";
        std::cout << std::string(65, '-') << "\n";

        for (const auto& hist : history_result) {
            std::cout << std::left
                      << std::setw(15) << (hist[0].empty() ? "---" : hist[0])
                      << std::setw(15) << hist[1]
                      << std::setw(20) << hist[2].substr(0, 16)
                      << std::setw(15) << hist[3]
                      << "\n";
        }
    }
}

void Manager::changeOrderStatus() {
    std::cout << "\n=== Изменение статуса заказа ===\n";

    // Показываем заказы, которые менеджер может обрабатывать
    std::string available_orders_query = R"(
        SELECT o.order_id, u.name, o.status, o.total_price
        FROM orders o
        JOIN users u ON o.user_id = u.user_id
        WHERE o.status IN ('processing', 'pending')
        ORDER BY o.order_date ASC
    )";

    auto orders = db->executeQuery(available_orders_query);

    if (orders.empty()) {
        std::cout << "Нет заказов для обработки\n";
        return;
    }

    std::cout << "Доступные заказы для изменения статуса:\n";
    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(20) << "Покупатель"
              << std::setw(15) << "Текущий статус"
              << std::setw(12) << "Сумма"
              << "\n";
    std::cout << std::string(55, '-') << "\n";

    for (const auto& order : orders) {
        std::cout << std::left
                  << std::setw(8) << order[0]
                  << std::setw(20) << (order[1].length() > 18 ? order[1].substr(0, 15) + "..." : order[1])
                  << std::setw(15) << order[2]
                  << std::setw(12) << order[3]
                  << "\n";
    }

    std::cout << "\nВведите ID заказа для изменения статуса: ";
    int order_id;
    std::cin >> order_id;

    std::cout << "Доступные статусы для изменения:\n";
    std::cout << "1. processing (в обработке)\n";
    std::cout << "2. completed (завершен)\n";
    std::cout << "3. canceled (отменен) - только для pending/processing\n";
    std::cout << "4. returned (возвращен)\n";
    std::cout << "Выберите новый статус (1-4): ";

    int status_choice;
    std::cin >> status_choice;

    std::string new_status;
    switch(status_choice) {
        case 1: new_status = "processing"; break;
        case 2: new_status = "completed"; break;
        case 3: new_status = "canceled"; break;
        case 4: new_status = "returned"; break;
        default:
            std::cout << "Неверный выбор статуса\n";
            return;
    }

    // Очищаем буфер ввода
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Причина изменения статуса (опционально): ";
    std::string reason;
    std::getline(std::cin, reason);

    try {
        // Используем хранимую процедуру для изменения статуса
        std::string call_proc = "CALL change_order_status(" +
                               std::to_string(order_id) + ", " +
                               std::to_string(user_id) + ", '" +
                               new_status + "', '" +
                               reason + "')";

        db->beginTransaction();
        db->executeNonQuery(call_proc);
        db->commitTransaction();

        std::cout << "Статус заказа #" << order_id << " изменен на '" << new_status << "'\n";

    } catch (const std::exception& e) {
        db->rollbackTransaction();
        std::cerr << "Ошибка при изменении статуса: " << e.what() << std::endl;
        std::cout << "Возможно, у вас нет прав на это изменение или заказ не существует\n";
    }
}

void Manager::viewMyApprovedOrders() {
    std::cout << "\n=== История утверждённых заказов (только мной) ===\n";

    std::string query = R"(
        SELECT o.order_id, u.name as customer_name,
               o.total_price, o.status, o.order_date,
               al.performed_at as approved_date
        FROM orders o
        JOIN users u ON o.user_id = u.user_id
        JOIN audit_log al ON o.order_id = al.entity_id
            AND al.entity_type = 'order'
            AND al.operation = 'approve'
            AND al.performed_by = )" + std::to_string(user_id) + R"(
        WHERE o.status != 'pending'
        ORDER BY al.performed_at DESC
        LIMIT 50
    )";

    auto result = db->executeQuery(query);

    if (result.empty()) {
        std::cout << "Вы еще не утвердили ни одного заказа\n";
        return;
    }

    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(20) << "Покупатель"
              << std::setw(12) << "Сумма"
              << std::setw(15) << "Статус"
              << std::setw(15) << "Дата утверждения"
              << "\n";
    std::cout << std::string(75, '-') << "\n";

    for (const auto& row : result) {
        std::cout << std::left
                  << std::setw(8) << row[0]
                  << std::setw(20) << (row[1].length() > 18 ? row[1].substr(0, 15) + "..." : row[1])
                  << std::setw(12) << row[2]
                  << std::setw(15) << row[3]
                  << std::setw(15) << row[5].substr(0, 10)
                  << "\n";
    }
}

void Manager::viewStatusHistory() {
    std::cout << "\n=== Просмотр истории статусов заказов ===\n";

    // Показываем заказы, с которыми работал менеджер
    std::string my_orders_query = R"(
        SELECT DISTINCT o.order_id, u.name as customer_name, o.status
        FROM orders o
        JOIN users u ON o.user_id = u.user_id
        WHERE EXISTS (
            SELECT 1 FROM order_status_history
            WHERE order_id = o.order_id AND changed_by = )" + std::to_string(user_id) + R"(
        ) OR EXISTS (
            SELECT 1 FROM audit_log
            WHERE entity_type = 'order' AND entity_id = o.order_id
            AND performed_by = )" + std::to_string(user_id) + R"(
        )
        ORDER BY o.order_id DESC
        LIMIT 20
    )";

    auto my_orders = db->executeQuery(my_orders_query);

    if (my_orders.empty()) {
        std::cout << "Вы еще не работали ни с одним заказом\n";
        return;
    }

    std::cout << "Заказы, с которыми вы работали:\n";
    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(25) << "Покупатель"
              << std::setw(15) << "Текущий статус"
              << "\n";
    std::cout << std::string(48, '-') << "\n";

    for (const auto& order : my_orders) {
        std::cout << std::left
                  << std::setw(8) << order[0]
                  << std::setw(25) << (order[1].length() > 23 ? order[1].substr(0, 20) + "..." : order[1])
                  << std::setw(15) << order[2]
                  << "\n";
    }

    std::cout << "\nВведите ID заказа для просмотра истории (0 - все мои изменения): ";
    int order_id;
    std::cin >> order_id;

    std::string history_query;

    if (order_id == 0) {
        // Показываем все изменения, сделанные менеджером
        history_query = R"(
            SELECT osh.order_id,
                   u.name as customer_name,
                   osh.old_status,
                   osh.new_status,
                   osh.changed_at,
                   (SELECT name FROM users WHERE user_id = osh.changed_by) as changed_by_name
            FROM order_status_history osh
            JOIN orders o ON osh.order_id = o.order_id
            JOIN users u ON o.user_id = u.user_id
            WHERE osh.changed_by = )" + std::to_string(user_id) + R"(
            ORDER BY osh.changed_at DESC
            LIMIT 30
        )";
    } else {
        // Показываем историю для конкретного заказа
        history_query = R"(
            SELECT osh.order_id,
                   u.name as customer_name,
                   osh.old_status,
                   osh.new_status,
                   osh.changed_at,
                   (SELECT name FROM users WHERE user_id = osh.changed_by) as changed_by_name
            FROM order_status_history osh
            JOIN orders o ON osh.order_id = o.order_id
            JOIN users u ON o.user_id = u.user_id
            WHERE osh.order_id = )" + std::to_string(order_id) + R"(
            ORDER BY osh.changed_at DESC
        )";
    }

    auto history_result = db->executeQuery(history_query);

    if (history_result.empty()) {
        if (order_id == 0) {
            std::cout << "Вы еще не изменяли статусы заказов\n";
        } else {
            std::cout << "История изменений для заказа #" << order_id << " не найдена\n";
        }
        return;
    }

    std::cout << "\nИстория изменений статусов:\n";
    std::cout << std::left
              << std::setw(8) << "Заказ"
              << std::setw(20) << "Покупатель"
              << std::setw(15) << "Старый статус"
              << std::setw(15) << "Новый статус"
              << std::setw(20) << "Дата изменения"
              << std::setw(15) << "Изменен"
              << "\n";
    std::cout << std::string(93, '-') << "\n";

    for (const auto& hist : history_result) {
        std::cout << std::left
                  << std::setw(8) << hist[0]
                  << std::setw(20) << (hist[1].length() > 18 ? hist[1].substr(0, 15) + "..." : hist[1])
                  << std::setw(15) << (hist[2].empty() ? "---" : hist[2])
                  << std::setw(15) << hist[3]
                  << std::setw(20) << hist[4].substr(0, 16)
                  << std::setw(15) << hist[5]
                  << "\n";
    }
}

// Вспомогательная функция для логирования (уже есть в базовом классе User)
void Manager::logAudit(const std::string& entity_type, int entity_id, const std::string& operation) {
    std::string query = "INSERT INTO audit_log (entity_type, entity_id, operation, performed_by) "
                       "VALUES ('" + entity_type + "', " +
                       std::to_string(entity_id) + ", '" +
                       operation + "', " +
                       std::to_string(user_id) + ")";
    db->executeNonQuery(query);
}