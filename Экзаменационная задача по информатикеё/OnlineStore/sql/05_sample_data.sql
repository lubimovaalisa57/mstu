#include "User.h"
#include "DatabaseConnection.h"
#include <iostream>
#include <iomanip>

User::User(int id, std::string n, std::string e, std::string r, 
           std::shared_ptr<DatabaseConnection<std::string>> database)
    : user_id(id), name(std::move(n)), email(std::move(e)), 
      role(std::move(r)), db(std::move(database)) {}

void User::viewOrderStatus(int order_id) {
    std::string query = "SELECT get_order_status(" + std::to_string(order_id) + ")";
    auto result = db->executeQuery(query);
    
    if (!result.empty() && !result[0].empty()) {
        std::cout << "Статус заказа ID " << order_id << ": " << result[0][0] << "\n";
} else {
        std::cout << "Заказ не найден\n";
}
}

void User::cancelOrder(int order_id) {
    std::string query = "CALL update_order_status(" + 
                       std::to_string(order_id) + ", 'canceled', " + 
                       std::to_string(user_id) + ")";
    
    try {
        db->beginTransaction();
        db->executeNonQuery(query);
        db->commitTransaction();
        std::cout << "Заказ отменен\n";
} catch (const std::exception& e) {
        db->rollbackTransaction();
        std::cerr << "Ошибка отмены заказа: " << e.what() << std::endl;
}
}

void User::viewOrderStatusHistory(int order_id) {
    std::cout << "\n=== История статусов заказа ID: " << order_id << " ===\n";
    
    std::string query = "SELECT * FROM get_order_status_history(" + std::to_string(order_id) + ")";
    auto result = db->executeQuery(query);
    
    if (result.empty()) {
        std::cout << "История изменений не найдена\n";
        return;
}
    
    std::cout << std::left << std::setw(10) << "ID" 
              << std::setw(20) << "Старый статус"
              << std::setw(20) << "Новый статус"
              << std::setw(25) << "Дата изменения"
              << std::setw(20) << "Кем изменен" << "\n";

for (const auto& row : result) {
        std::cout << std::left << std::setw(10) << row[0]
                  << std::setw(20) << (row[1].empty() ? "N/A" : row[1])
                  << std::setw(20) << row[2]
                  << std::setw(25) << row[3]
                  << std::setw(20) << row[4] << "\n";
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
        std::cerr << "Ошибка логирования: " << e.what() << std::endl;
}
}