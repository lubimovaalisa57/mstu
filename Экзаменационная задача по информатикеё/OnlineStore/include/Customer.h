#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"

class Customer : public User {
public:
    Customer(int id, std::string n, std::string e,
             std::shared_ptr<DatabaseConnection<std::string>> database);

    void showMenu() override;
    void performAction(int choice) override;

    void createOrder();
    void addToOrder();
    void removeFromOrder();
    void viewMyOrders();
    void makePayment();
    void returnOrder();
    void viewOrderStatusCustomer();

private:
    int current_order_id = -1;
    void displayProducts();
    void displayCart(int order_id);
};

#endif