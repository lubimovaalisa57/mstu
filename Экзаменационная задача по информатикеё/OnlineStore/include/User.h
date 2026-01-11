#ifndef USER_H
#define USER_H

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "DatabaseConnection.h"

class Order;

class User {
protected:
    int user_id;
    std::string name;
    std::string email;
    std::string role;
    std::shared_ptr<DatabaseConnection<std::string>> db;
    std::vector<std::shared_ptr<Order>> orders;

public:
    User(int id, std::string n, std::string e, std::string r,
         std::shared_ptr<DatabaseConnection<std::string>> database);
    virtual ~User() = default;

    virtual void showMenu() = 0;
    virtual void performAction(int choice) = 0;

    void viewOrderStatus(int order_id);
    void cancelOrder(int order_id);
    void viewOrderStatusHistory(int order_id);

    int getUserId() const { return user_id; }
    std::string getRole() const { return role; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }

protected:
    void logAudit(const std::string& entity_type, int entity_id,
                  const std::string& operation);
};

#endif