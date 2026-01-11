#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <string>
#include <chrono>
#include <memory>
#include "PaymentStrategy.h"

class Payment {
private:
    int payment_id;
    int order_id;
    double amount;
    std::string payment_method;
    std::string status;
    std::chrono::system_clock::time_point payment_date;
    std::string transaction_id;
    std::unique_ptr<PaymentStrategy> strategy;

public:
    Payment(int pid, int oid, double amt, std::string method, std::unique_ptr<PaymentStrategy> strat)
        : payment_id(pid), order_id(oid), amount(amt),
          payment_method(std::move(method)), status("pending"),
          payment_date(std::chrono::system_clock::now()),
          strategy(std::move(strat)) {}

    bool processPayment() {
        if (strategy->pay(amount)) {
            status = "completed";
            return true;
        }
        status = "failed";
        return false;
    }

    void refund() {
        status = "refunded";
        // Здесь можно добавить логику возврата через стратегию
    }

    bool isCompleted() const { return status == "completed"; }
    bool isFailed() const { return status == "failed"; }
    bool isRefunded() const { return status == "refunded"; }

    void displayInfo() const {
        std::cout << "Платеж ID: " << payment_id
                  << ", Метод: " << payment_method
                  << ", Сумма: " << amount
                  << ", Статус: " << status
                  << ", Дата: " << std::chrono::system_clock::to_time_t(payment_date) << "\n";
    }

    std::string getStatus() const { return status; }
    double getAmount() const { return amount; }
    std::string getMethod() const { return payment_method; }
};

#endif