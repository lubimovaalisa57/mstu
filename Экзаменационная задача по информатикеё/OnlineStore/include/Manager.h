#ifndef MANAGER_H
#define MANAGER_H

#include "User.h"
#include <memory>
#include <string>

class Manager : public User {
public:
    Manager(int id, std::string n, std::string e,
            std::shared_ptr<DatabaseConnection<std::string>> database);

    void showMenu() override;
    void performAction(int choice) override;

private:
    void viewPendingOrders();
    void approveOrder();
    void updateStock();
    void viewOrderDetails();          // Добавлено
    void changeOrderStatus();         // Добавлено
    void viewMyApprovedOrders();
    void viewStatusHistory();         // Добавлено

    // Вспомогательные методы
    void logAudit(const std::string& entity_type, int entity_id, const std::string& operation);
};

#endif // MANAGER_H