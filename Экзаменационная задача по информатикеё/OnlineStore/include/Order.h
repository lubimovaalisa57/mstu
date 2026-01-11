#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <algorithm>
#include <numeric>
#include "OrderItem.h"
#include "Payment.h"

class Order {
private:
    int order_id;
    int user_id;
    std::string status;
    double total_price;
    std::chrono::system_clock::time_point order_date;
    std::vector<std::shared_ptr<OrderItem>> items;
    std::unique_ptr<Payment> payment;

public:
    Order(int id, int uid, std::string stat, double total)
        : order_id(id), user_id(uid), status(std::move(stat)),
          total_price(total), order_date(std::chrono::system_clock::now()) {}

    int getOrderId() const { return order_id; }
    int getUserId() const { return user_id; }
    std::string getStatus() const { return status; }
    double getTotalPrice() const { return total_price; }

    void setStatus(const std::string& new_status) { status = new_status; }
    void setTotalPrice(double price) { total_price = price; }

    void addItem(std::shared_ptr<OrderItem> item) {
        auto it = std::find_if(items.begin(), items.end(),
            [item](const auto& existing_item) {
                return existing_item->getProductId() == item->getProductId();
            });

        if (it != items.end()) {
            (*it)->setQuantity((*it)->getQuantity() + item->getQuantity());
        } else {
            items.push_back(item);
        }

        total_price += item->getTotalPrice();
    }

    void removeItem(int product_id) {
        auto it = std::find_if(items.begin(), items.end(),
            [product_id](const auto& item) {
                return item->getProductId() == product_id;
            });

        if (it != items.end()) {
            total_price -= (*it)->getTotalPrice();
            items.erase(it);
        }
    }

    void setPayment(std::unique_ptr<Payment> pay) {
        payment = std::move(pay);
    }

    bool isPaid() const {
        return payment != nullptr && payment->isCompleted();
    }

    void displayOrderInfo() const {
        std::cout << "Заказ ID: " << order_id
                  << ", Пользователь: " << user_id
                  << ", Статус: " << status
                  << ", Сумма: " << total_price << "\n";

        if (!items.empty()) {
            std::cout << "Товары в заказе:\n";
            for (const auto& item : items) {
                item->displayInfo();
            }
        }

        if (payment) {
            payment->displayInfo();
        }
    }

    const std::vector<std::shared_ptr<OrderItem>>& getItems() const {
        return items;
    }

    int getItemCount() const {
        return std::accumulate(items.begin(), items.end(), 0,
            [](int sum, const auto& item) {
                return sum + item->getQuantity();
            });
    }

    bool isEmpty() const {
        return items.empty();
    }

    void clear() {
        items.clear();
        total_price = 0.0;
        status = "pending";
    }
};

#endif