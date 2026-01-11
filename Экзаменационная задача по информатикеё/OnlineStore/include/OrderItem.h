#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <iostream>
#include <string>
#include <memory>

class OrderItem {
private:
    int order_item_id;
    int order_id;
    int product_id;
    int quantity;
    double price;

public:
    OrderItem(int id, int oid, int pid, int qty, double pr)
        : order_item_id(id), order_id(oid), product_id(pid), quantity(qty), price(pr) {}

    // Геттеры
    int getItemId() const { return order_item_id; }
    int getOrderId() const { return order_id; }
    int getProductId() const { return product_id; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    double getTotalPrice() const { return quantity * price; }

    // Сеттеры
    void setQuantity(int qty) { quantity = qty; }
    void setPrice(double pr) { price = pr; }

    void displayInfo() const {
        std::cout << "  Товар ID: " << product_id
                  << ", Количество: " << quantity
                  << ", Цена за шт: " << price
                  << ", Итого: " << getTotalPrice() << "\n";
    }
};

#endif