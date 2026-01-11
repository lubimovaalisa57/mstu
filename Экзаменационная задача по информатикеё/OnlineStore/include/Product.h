#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <memory>

class Product {
private:
    int product_id;
    std::string name;
    double price;
    int stock_quantity;

public:
    Product(int id, std::string n, double p, int stock)
        : product_id(id), name(std::move(n)), price(p), stock_quantity(stock) {}

    // Геттеры
    int getId() const { return product_id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getStockQuantity() const { return stock_quantity; }

    // Сеттеры
    void setPrice(double new_price) { price = new_price; }
    void setStockQuantity(int quantity) { stock_quantity = quantity; }
    void setName(const std::string& new_name) { name = new_name; }

    // Методы
    void displayInfo() const {
        std::cout << "ID: " << product_id
                  << ", Название: " << name
                  << ", Цена: " << price
                  << ", На складе: " << stock_quantity << "\n";
    }

    bool isAvailable(int requested_quantity = 1) const {
        return stock_quantity >= requested_quantity;
    }

    void reduceStock(int quantity) {
        if (quantity <= stock_quantity) {
            stock_quantity -= quantity;
        }
    }

    void increaseStock(int quantity) {
        stock_quantity += quantity;
    }
};

#endif