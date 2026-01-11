#include "../include/User.h"
#include "../include/DatabaseConnection.h"
#include <iostream>
#include <iomanip>

User::User(int id, std::string n, std::string e, std::string r,
           std::shared_ptr<DatabaseConnection<std::string>> database)
    : user_id(id), name(std::move(n)), email(std::move(e)),
      role(std::move(r)), db(std::move(database)) {}

void User::viewOrderStatus(int order_id) {
    std::string query = "SELECT status FROM orders WHERE order_id = " + std::to_string(order_id);
    auto result = db->executeQuery(query);

    if (!result.empty() && !result[0].empty()) {
        std::cout << "Статус заказа: " << result[0][0] << "\n";
    } else {
        std::cout << "Заказ не найден\n";
    }
}

void User::cancelOrder(int order_id) {
    if (role != "customer") {
        std::cout << "Только покупатели могут отменять заказы\n";
        return;
    }

    std::string query = "UPDATE orders SET status = 'canceled' WHERE order_id = " +
                       std::to_string(order_id) + " AND user_id = " + std::to_string(user_id);

    try {
        db->beginTransaction();
        db->executeNonQuery(query);

        // Проверим, изменился ли заказ
        std::string check_query = "SELECT status FROM orders WHERE order_id = " +
                                 std::to_string(order_id);
        auto result = db->executeQuery(check_query);

        if (!result.empty() && result[0][0] == "canceled") {
            logAudit("order", order_id, "cancel");
            db->commitTransaction();
            std::cout << "Заказ отменен\n";
        } else {
            db->rollbackTransaction();
            std::cout << "Не удалось отменить заказ\n";
        }
    } catch (const std::exception& e) {
        db->rollbackTransaction();
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void User::viewOrderStatusHistory(int order_id) {
    std::cout << "История статусов заказа ID: " << order_id << "\n";

    std::string query = "SELECT old_status, new_status, changed_at FROM order_status_history "
                       "WHERE order_id = " + std::to_string(order_id) + " ORDER BY changed_at";

    auto result = db->executeQuery(query);

    if (result.empty()) {
        std::cout << "История не найдена\n";
        return;
    }

    for (const auto& row : result) {
        std::cout << "С: " << (row[0].empty() ? "Нет" : row[0])
                  << " -> На: " << row[1]
                  << " Время: " << row[2] << "\n";
    }
}

void User::logAudit(const std::string& entity_type, int entity_id,
                    const std::string& operation) {
    std::string query = "INSERT INTO audit_log (entity_type, entity_id, operation, performed_by) "
                       "VALUES ('" + entity_type + "', " +
                       std::to_string(entity_id) + ", '" +
                       operation + "', " +
                       std::to_string(user_id) + ")";

    try {
        db->executeNonQuery(query);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка аудита: " << e.what() << std::endl;
    }
}