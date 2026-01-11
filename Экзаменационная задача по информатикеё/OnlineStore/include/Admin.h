/*
#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    Admin(int id, std::string n, std::string e,
          std::shared_ptr<DatabaseConnection<std::string>> database);

    void showMenu() override;
    void performAction(int choice) override;

    void addProduct();
    void updateProduct();
    void deleteProduct();
    void viewAllOrders();
    void viewOrderDetails(int order_id);
    void updateOrderStatus();
    void viewOrderStatusHistoryMenu();
    void viewAuditLog();
    void generateReport();
    void manageUsers();
};

#endif
*/
#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <memory>
#include <string>

class Admin : public User {
public:
    Admin(int id, std::string n, std::string e,
          std::shared_ptr<DatabaseConnection<std::string>> database);

    void showMenu() override;
    void performAction(int choice) override;

private:
    void addProduct();
    void updateProduct();
    void deleteProduct();
    void viewAllOrders();
    void viewOrderDetails();
    void changeOrderStatus();
    void viewOrderStatusHistory();
    void viewAuditLog();
    void generateReportCSV();

    std::string escapeString(const std::string& str);
};

#endif // ADMIN_H