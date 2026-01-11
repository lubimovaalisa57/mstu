#include "../include/Admin.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>    // Для getenv
#include <sys/stat.h> // Для stat
#include <unistd.h>

Admin::Admin(int id, std::string n, std::string e,
             std::shared_ptr<DatabaseConnection<std::string>> database)
    : User(id, std::move(n), std::move(e), "admin", database) {}

void Admin::showMenu() {
    std::cout << "\n=== Меню администратора ===\n";
    std::cout << "1. Добавить новый продукт\n";
    std::cout << "2. Обновить информацию о продукте\n";
    std::cout << "3. Удалить продукт\n";
    std::cout << "4. Просмотр всех заказов\n";
    std::cout << "5. Просмотр деталей заказа\n";
    std::cout << "6. Изменить статус заказа\n";
    std::cout << "7. Просмотр истории статусов заказа\n";
    std::cout << "8. Просмотр журнала аудита\n";
    std::cout << "9. Сформировать отчёт (CSV)\n";
    std::cout << "0. Выход\n";
    std::cout << "Выбор: ";
}

void Admin::performAction(int choice) {
    switch(choice) {
        case 1: addProduct(); break;
        case 2: updateProduct(); break;
        case 3: deleteProduct(); break;
        case 4: viewAllOrders(); break;
        case 5: viewOrderDetails(); break;
        case 6: changeOrderStatus(); break;
        case 7: viewOrderStatusHistory(); break;
        case 8: viewAuditLog(); break;
        case 9: generateReportCSV(); break;
        case 10:
            std::cout << "Выход из меню администратора\n";
            return; // Возвращаем управление в главное меню
        default:
            std::cout << "Неверный выбор\n";
    }
}

void Admin::addProduct() {
    std::cout << "\n=== Добавление нового продукта ===\n";

    std::string name;
    double price;
    int quantity;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введите название продукта: ";
    std::getline(std::cin, name);

    std::cout << "Введите цену продукта: ";
    std::cin >> price;

    std::cout << "Введите количество на складе: ";
    std::cin >> quantity;

    if (price <= 0) {
        std::cout << "Цена должна быть больше 0\n";
        return;
    }

    if (quantity < 0) {
        std::cout << "Количество не может быть отрицательным\n";
        return;
    }

    try {
        db->beginTransaction();

        std::string query = "INSERT INTO products (name, price, stock_quantity) "
                           "VALUES ('" + escapeString(name) + "', " +
                           std::to_string(price) + ", " +
                           std::to_string(quantity) + ") RETURNING product_id";

        auto result = db->executeQuery(query);

        if (!result.empty()) {
            int product_id = std::stoi(result[0][0]);

            // Логируем действие
            std::string audit_query = "INSERT INTO audit_log (entity_type, entity_id, "
                                     "operation, performed_by, details) "
                                     "VALUES ('product', " + std::to_string(product_id) +
                                     ", 'insert', " + std::to_string(user_id) +
                                     ", 'Добавлен новый продукт: " + escapeString(name) +
                                     ", цена: " + std::to_string(price) +
                                     ", количество: " + std::to_string(quantity) + "')";
            db->executeNonQuery(audit_query);

            db->commitTransaction();
            std::cout << "Продукт успешно добавлен с ID: " << product_id << "\n";
        }

    } catch (const std::exception& e) {
        db->rollbackTransaction();

        // Логируем ошибку
        std::string error_query = "INSERT INTO audit_log (entity_type, entity_id, "
                                 "operation, performed_by, details) "
                                 "VALUES ('system', 0, 'error', " +
                                 std::to_string(user_id) +
                                 ", 'Ошибка добавления продукта: " +
                                 escapeString(e.what()) + "')";
        try {
            db->executeNonQuery(error_query);
        } catch (...) {
            // Игнорируем ошибку логирования
        }

        std::cerr << "Ошибка при добавлении продукта: " << e.what() << std::endl;
    }
}

void Admin::updateProduct() {
    std::cout << "\n=== Обновление информации о продукте ===\n";

    // Показываем все продукты
    std::string query = "SELECT product_id, name, price, stock_quantity FROM products "
                       "ORDER BY product_id";
    auto products = db->executeQuery(query);

    if (products.empty()) {
        std::cout << "В базе нет продуктов\n";
        return;
    }

    std::cout << "Список продуктов:\n";
    std::cout << std::left
              << std::setw(6) << "ID"
              << std::setw(25) << "Название"
              << std::setw(10) << "Цена"
              << std::setw(12) << "Количество"
              << "\n";
    std::cout << std::string(53, '-') << "\n";

    for (const auto& product : products) {
        std::cout << std::left
                  << std::setw(6) << product[0]
                  << std::setw(25) << (product[1].length() > 23 ? product[1].substr(0, 20) + "..." : product[1])
                  << std::setw(10) << product[2]
                  << std::setw(12) << product[3]
                  << "\n";
    }

    std::cout << "\nВведите ID продукта для обновления: ";
    int product_id;
    std::cin >> product_id;

    // Получаем текущую информацию о продукте
    std::string check_query = "SELECT name, price, stock_quantity FROM products "
                             "WHERE product_id = " + std::to_string(product_id);
    auto result = db->executeQuery(check_query);

    if (result.empty()) {
        std::cout << "Продукт с ID " << product_id << " не найден\n";
        return;
    }

    std::string old_name = result[0][0];
    double old_price = std::stod(result[0][1]);
    int old_quantity = std::stoi(result[0][2]);

    std::cout << "Текущие данные продукта:\n";
    std::cout << "Название: " << old_name << "\n";
    std::cout << "Цена: " << old_price << "\n";
    std::cout << "Количество: " << old_quantity << "\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string new_name;
    std::cout << "Введите новое название (оставьте пустым для сохранения текущего): ";
    std::getline(std::cin, new_name);

    std::string price_str;
    std::cout << "Введите новую цену (оставьте пустым для сохранения текущей): ";
    std::getline(std::cin, price_str);

    std::string quantity_str;
    std::cout << "Введите новое количество (оставьте пустым для сохранения текущего): ";
    std::getline(std::cin, quantity_str);

    double new_price = old_price;
    int new_quantity = old_quantity;

    if (!price_str.empty()) {
        try {
            new_price = std::stod(price_str);
            if (new_price <= 0) {
                std::cout << "Цена должна быть больше 0\n";
                return;
            }
        } catch (...) {
            std::cout << "Неверный формат цены\n";
            return;
        }
    }

    if (!quantity_str.empty()) {
        try {
            new_quantity = std::stoi(quantity_str);
            if (new_quantity < 0) {
                std::cout << "Количество не может быть отрицательным\n";
                return;
            }
        } catch (...) {
            std::cout << "Неверный формат количества\n";
            return;
        }
    }

    try {
        db->beginTransaction();

        // Формируем запрос на обновление
        std::string update_query = "UPDATE products SET ";
        bool has_updates = false;

        if (!new_name.empty() && new_name != old_name) {
            update_query += "name = '" + escapeString(new_name) + "'";
            has_updates = true;
        }

        if (new_price != old_price) {
            if (has_updates) update_query += ", ";
            update_query += "price = " + std::to_string(new_price);
            has_updates = true;
        }

        if (new_quantity != old_quantity) {
            if (has_updates) update_query += ", ";
            update_query += "stock_quantity = " + std::to_string(new_quantity);
            has_updates = true;
        }

        if (!has_updates) {
            std::cout << "Нет изменений для обновления\n";
            db->rollbackTransaction();
            return;
        }

        update_query += " WHERE product_id = " + std::to_string(product_id);

        db->executeNonQuery(update_query);

        // Логируем действие
        std::string changes;
        if (!new_name.empty() && new_name != old_name) changes += "Название: " + old_name + " -> " + new_name + "; ";
        if (new_price != old_price) changes += "Цена: " + std::to_string(old_price) + " -> " + std::to_string(new_price) + "; ";
        if (new_quantity != old_quantity) changes += "Количество: " + std::to_string(old_quantity) + " -> " + std::to_string(new_quantity);

        std::string audit_query = "INSERT INTO audit_log (entity_type, entity_id, "
                                 "operation, performed_by, details) "
                                 "VALUES ('product', " + std::to_string(product_id) +
                                 ", 'update', " + std::to_string(user_id) +
                                 ", 'Обновление продукта: " + changes + "')";
        db->executeNonQuery(audit_query);

        db->commitTransaction();
        std::cout << "Продукт успешно обновлен\n";

    } catch (const std::exception& e) {
        db->rollbackTransaction();

        // Логируем ошибку
        std::string error_query = "INSERT INTO audit_log (entity_type, entity_id, "
                                 "operation, performed_by, details) "
                                 "VALUES ('system', 0, 'error', " +
                                 std::to_string(user_id) +
                                 ", 'Ошибка обновления продукта " +
                                 std::to_string(product_id) + ": " +
                                 escapeString(e.what()) + "')";
        try {
            db->executeNonQuery(error_query);
        } catch (...) {
            // Игнорируем ошибку логирования
        }

        std::cerr << "Ошибка при обновлении продукта: " << e.what() << std::endl;
    }
}

void Admin::deleteProduct() {
    std::cout << "\n=== Удаление продукта ===\n";

    // Показываем продукты с количеством 0 (рекомендуется к удалению)
    std::string query = "SELECT product_id, name, price, stock_quantity FROM products "
                       "WHERE stock_quantity = 0 "
                       "ORDER BY product_id";
    auto products = db->executeQuery(query);

    if (!products.empty()) {
        std::cout << "Продукты с нулевым количеством (рекомендуется к удалению):\n";
        std::cout << std::left
                  << std::setw(6) << "ID"
                  << std::setw(25) << "Название"
                  << std::setw(10) << "Цена"
                  << "\n";
        std::cout << std::string(41, '-') << "\n";

        for (const auto& product : products) {
            std::cout << std::left
                      << std::setw(6) << product[0]
                      << std::setw(25) << (product[1].length() > 23 ? product[1].substr(0, 20) + "..." : product[1])
                      << std::setw(10) << product[2]
                      << "\n";
        }
        std::cout << "\n";
    }

    std::cout << "Введите ID продукта для удаления: ";
    int product_id;
    std::cin >> product_id;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Проверяем, есть ли продукт в заказах
    std::string check_query = "SELECT 1 FROM order_items WHERE product_id = " +
                             std::to_string(product_id) + " LIMIT 1";
    auto check_result = db->executeQuery(check_query);

    if (!check_result.empty()) {
        std::cout << "Продукт присутствует в заказах. Удаление невозможно.\n";
        return;
    }

    // Получаем информацию о продукте для лога
    std::string product_query = "SELECT name FROM products WHERE product_id = " +
                               std::to_string(product_id);
    auto product_info = db->executeQuery(product_query);

    if (product_info.empty()) {
        std::cout << "Продукт с ID " << product_id << " не найден\n";
        return;
    }

    std::string product_name = product_info[0][0];

    std::cout << "Вы уверены, что хотите удалить продукт \"" << product_name
              << "\"? (да/нет): ";
    std::string confirm;
    std::getline(std::cin, confirm);

    if (confirm != "да" && confirm != "д" && confirm != "yes" && confirm != "y") {
        std::cout << "Операция отменена\n";
        return;
    }

    try {
        db->beginTransaction();

        std::string delete_query = "DELETE FROM products WHERE product_id = " +
                                  std::to_string(product_id);
        db->executeNonQuery(delete_query);

        // Логируем действие
        std::string audit_query = "INSERT INTO audit_log (entity_type, entity_id, "
                                 "operation, performed_by, details) "
                                 "VALUES ('product', " + std::to_string(product_id) +
                                 ", 'delete', " + std::to_string(user_id) +
                                 ", 'Удален продукт: " + escapeString(product_name) + "')";
        db->executeNonQuery(audit_query);

        db->commitTransaction();
        std::cout << "Продукт успешно удален\n";

    } catch (const std::exception& e) {
        db->rollbackTransaction();

        // Логируем ошибку
        std::string error_query = "INSERT INTO audit_log (entity_type, entity_id, "
                                 "operation, performed_by, details) "
                                 "VALUES ('system', 0, 'error', " +
                                 std::to_string(user_id) +
                                 ", 'Ошибка удаления продукта " +
                                 std::to_string(product_id) + ": " +
                                 escapeString(e.what()) + "')";
        try {
            db->executeNonQuery(error_query);
        } catch (...) {
            // Игнорируем ошибку логирования
        }

        std::cerr << "Ошибка при удалении продукта: " << e.what() << std::endl;
    }
}

void Admin::viewAllOrders() {
    std::cout << "\n=== Просмотр всех заказов ===\n";

    std::string query = R"(
        SELECT o.order_id, u.name as customer_name,
               o.status, o.total_price, o.order_date,
               COUNT(oi.order_item_id) as items_count,
               (SELECT MAX(changed_at) FROM order_status_history
                WHERE order_id = o.order_id) as last_update
        FROM orders o
        JOIN users u ON o.user_id = u.user_id
        LEFT JOIN order_items oi ON o.order_id = oi.order_id
        GROUP BY o.order_id, u.name, o.status, o.total_price, o.order_date
        ORDER BY o.order_date DESC
    )";

    auto result = db->executeQuery(query);

    if (result.empty()) {
        std::cout << "Нет заказов в системе\n";
        return;
    }

    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(20) << "Покупатель"
              << std::setw(15) << "Статус"
              << std::setw(12) << "Сумма"
              << std::setw(15) << "Дата заказа"
              << std::setw(10) << "Товаров"
              << "\n";
    std::cout << std::string(85, '-') << "\n";

    for (const auto& row : result) {
        std::cout << std::left
                  << std::setw(8) << row[0]
                  << std::setw(20) << (row[1].length() > 18 ? row[1].substr(0, 15) + "..." : row[1])
                  << std::setw(15) << row[2]
                  << std::setw(12) << row[3]
                  << std::setw(15) << row[4].substr(0, 10)
                  << std::setw(10) << row[5]
                  << "\n";
    }
}

void Admin::viewOrderDetails() {
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

        double items_total = 0;
        for (const auto& item : items_result) {
            std::cout << std::left
                      << std::setw(30) << (item[0].length() > 28 ? item[0].substr(0, 25) + "..." : item[0])
                      << std::setw(10) << item[1]
                      << std::setw(12) << item[2]
                      << std::setw(12) << item[3]
                      << "\n";
            items_total += std::stod(item[3]);
        }
        std::cout << std::string(64, '-') << "\n";
        std::cout << std::left << std::setw(52) << "Итого по товарам: "
                  << std::setw(12) << items_total << "\n";
    }
}

void Admin::changeOrderStatus() {
    std::cout << "\n=== Изменение статуса заказа ===\n";

    // Показываем все заказы
    viewAllOrders();

    std::cout << "\nВведите ID заказа для изменения статуса: ";
    int order_id;
    std::cin >> order_id;

    std::cout << "Выберите новый статус:\n";
    std::cout << "1. pending (ожидание)\n";
    std::cout << "2. processing (в обработке)\n";
    std::cout << "3. completed (завершен)\n";
    std::cout << "4. canceled (отменен)\n";
    std::cout << "5. returned (возвращен)\n";
    std::cout << "Выберите статус (1-5): ";

    int status_choice;
    std::cin >> status_choice;

    std::string new_status;
    switch(status_choice) {
        case 1: new_status = "pending"; break;
        case 2: new_status = "processing"; break;
        case 3: new_status = "completed"; break;
        case 4: new_status = "canceled"; break;
        case 5: new_status = "returned"; break;
        default:
            std::cout << "Неверный выбор статуса\n";
            return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Причина изменения статуса: ";
    std::string reason;
    std::getline(std::cin, reason);

    if (reason.empty()) {
        reason = "Изменено администратором";
    }

    try {
        db->beginTransaction();

        // Получаем текущий статус
        std::string old_status_query = "SELECT status FROM orders WHERE order_id = " +
                                      std::to_string(order_id);
        auto old_status_result = db->executeQuery(old_status_query);

        if (old_status_result.empty()) {
            throw std::runtime_error("Заказ не найден");
        }

        std::string old_status = old_status_result[0][0];

        // Обновляем статус
        std::string update_query = "UPDATE orders SET status = '" + new_status +
                                  "', updated_at = CURRENT_TIMESTAMP " +
                                  "WHERE order_id = " + std::to_string(order_id);
        db->executeNonQuery(update_query);

        // Логируем в audit_log
        std::string audit_query = "INSERT INTO audit_log (entity_type, entity_id, "
                                 "operation, performed_by, details) "
                                 "VALUES ('order', " + std::to_string(order_id) +
                                 ", 'update', " + std::to_string(user_id) +
                                 ", 'Изменение статуса: " + old_status + " -> " +
                                 new_status + ". Причина: " + escapeString(reason) + "')";
        db->executeNonQuery(audit_query);

        // Логируем в order_status_history
        std::string history_query = "INSERT INTO order_status_history "
                                   "(order_id, old_status, new_status, changed_by) "
                                   "VALUES (" + std::to_string(order_id) +
                                   ", '" + old_status + "', '" + new_status + "', " +
                                   std::to_string(user_id) + ")";
        db->executeNonQuery(history_query);

        db->commitTransaction();
        std::cout << "Статус заказа #" << order_id << " изменен с '"
                  << old_status << "' на '" << new_status << "'\n";

    } catch (const std::exception& e) {
        db->rollbackTransaction();

        // Логируем ошибку
        std::string error_query = "INSERT INTO audit_log (entity_type, entity_id, "
                                 "operation, performed_by, details) "
                                 "VALUES ('system', 0, 'error', " +
                                 std::to_string(user_id) +
                                 ", 'Ошибка изменения статуса заказа " +
                                 std::to_string(order_id) + ": " +
                                 escapeString(e.what()) + "')";
        try {
            db->executeNonQuery(error_query);
        } catch (...) {
            // Игнорируем ошибку логирования
        }

        std::cerr << "Ошибка при изменении статуса: " << e.what() << std::endl;
    }
}

void Admin::viewOrderStatusHistory() {
    std::cout << "\n=== Просмотр истории статусов заказа ===\n";

    std::cout << "Введите ID заказа: ";
    int order_id;
    std::cin >> order_id;

    std::string query = R"(
        SELECT osh.history_id, osh.old_status, osh.new_status,
               osh.changed_at, u.name as changed_by_name
        FROM order_status_history osh
        JOIN users u ON osh.changed_by = u.user_id
        WHERE osh.order_id = )" + std::to_string(order_id) + R"(
        ORDER BY osh.changed_at DESC
    )";

    auto result = db->executeQuery(query);

    if (result.empty()) {
        std::cout << "История изменений для заказа #" << order_id << " не найдена\n";
        return;
    }

    std::cout << "\nИстория изменений статусов заказа #" << order_id << ":\n";
    std::cout << std::left
              << std::setw(6) << "ID"
              << std::setw(15) << "Старый статус"
              << std::setw(15) << "Новый статус"
              << std::setw(20) << "Дата изменения"
              << std::setw(20) << "Изменен"
              << "\n";
    std::cout << std::string(76, '-') << "\n";

    for (const auto& row : result) {
        std::cout << std::left
                  << std::setw(6) << row[0]
                  << std::setw(15) << (row[1].empty() ? "---" : row[1])
                  << std::setw(15) << row[2]
                  << std::setw(20) << row[3].substr(0, 16)
                  << std::setw(20) << row[4]
                  << "\n";
    }
}

void Admin::viewAuditLog() {
    std::cout << "\n=== Просмотр журнала аудита ===\n";

    std::string query = R"(
        SELECT al.log_id, al.entity_type, al.entity_id,
               al.operation, u.name as performed_by_name,
               al.performed_at, al.details
        FROM audit_log al
        LEFT JOIN users u ON al.performed_by = u.user_id
        ORDER BY al.performed_at DESC
        LIMIT 50
    )";

    auto result = db->executeQuery(query);

    if (result.empty()) {
        std::cout << "Журнал аудита пуст\n";
        return;
    }

    std::cout << std::left
              << std::setw(6) << "ID"
              << std::setw(10) << "Тип"
              << std::setw(8) << "Объект"
              << std::setw(12) << "Операция"
              << std::setw(15) << "Выполнил"
              << std::setw(20) << "Время"
              << std::setw(30) << "Детали"
              << "\n";
    std::cout << std::string(101, '-') << "\n";

    for (const auto& row : result) {
        std::cout << std::left
                  << std::setw(6) << row[0]
                  << std::setw(10) << row[1]
                  << std::setw(8) << row[2]
                  << std::setw(12) << row[3]
                  << std::setw(15) << (row[4].empty() ? "---" :
                      (row[4].length() > 13 ? row[4].substr(0, 10) + "..." : row[4]))
                  << std::setw(20) << row[5].substr(0, 16)
                  << std::setw(30) << (row[6].empty() ? "---" :
                      (row[6].length() > 28 ? row[6].substr(0, 25) + "..." : row[6]))
                  << "\n";
    }
}

void Admin::generateReportCSV() {
    std::cout << "\n=== Формирование отчёта (CSV) ===\n";

    std::cout << "Введите имя файла для отчета (без расширения): ";
    std::string filename;
    std::cin >> filename;

    // Абсолютный путь к папке reports
    std::string home_path = getenv("HOME");
    std::string reports_dir = home_path + "/Desktop/mstu/mstu/Экзаменационная задача по информатикеё/OnlineStore/reports";

    // Проверяем и создаем папку если нужно
    struct stat info;
    if (stat(reports_dir.c_str(), &info) != 0) {
        // Папка не существует, создаем
        std::string cmd = "mkdir -p \"" + reports_dir + "\"";
        system(cmd.c_str());
        std::cout << "Создана папка: " << reports_dir << "\n";
    }

    std::string full_path = reports_dir + "/" + filename + "_report.csv";

    std::cout << "Файл будет сохранен как: " << full_path << "\n";

    try {
        // Простой SQL запрос для отчета
        std::string report_query = R"(
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
                    FROM order_status_history
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

        auto report_data = db->executeQuery(report_query);

        if (report_data.empty()) {
            std::cout << "Нет данных для отчета\n";
            return;
        }

        // Создаем CSV файл
        std::ofstream csv_file;
        csv_file.open(full_path);

        if (!csv_file.is_open()) {
            std::cerr << "Ошибка: не могу открыть файл для записи\n";
            std::cerr << "Проверьте права доступа к папке: " << reports_dir << "\n";
            return;
        }

        // Заголовки CSV
        csv_file << "ID заказа;Покупатель;Статус заказа;Сумма заказа;"
                 << "Дата заказа;Последнее изменение статуса;"
                 << "Кол-во изменений статуса;Последняя операция аудита;"
                 << "Время последнего аудита;Всего записей аудита\n";

        // Данные
        for (const auto& row : report_data) {
            for (size_t i = 0; i < row.size(); ++i) {
                csv_file << row[i];
                if (i < row.size() - 1) {
                    csv_file << ";";
                }
            }
            csv_file << "\n";
        }

        csv_file.close();

        std::cout << "✓ Отчет успешно сохранен!\n";
        std::cout << "✓ Файл: " << full_path << "\n";
        std::cout << "✓ Записей: " << report_data.size() << "\n";

    } catch (const std::exception& e) {
        std::cerr << "✗ Ошибка: " << e.what() << std::endl;
    }
}

std::string Admin::escapeString(const std::string& str) {
    std::string escaped = str;
    // Простая эскейп-обработка для SQL
    size_t pos = 0;
    while ((pos = escaped.find("'", pos)) != std::string::npos) {
        escaped.replace(pos, 1, "''");
        pos += 2;
    }
    return escaped;
}