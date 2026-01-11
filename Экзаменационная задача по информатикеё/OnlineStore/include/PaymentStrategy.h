#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H

#include <iostream>
#include <string>
#include <memory>

class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual bool pay(double amount) = 0;
    virtual std::string getName() const = 0;
};

class CreditCardPayment : public PaymentStrategy {
public:
    bool pay(double amount) override;
    std::string getName() const override;
};

class EWalletPayment : public PaymentStrategy {
public:
    bool pay(double amount) override;
    std::string getName() const override;
};

class SBPPayment : public PaymentStrategy {
public:
    bool pay(double amount) override;
    std::string getName() const override;
};

// Фабричная функция для создания стратегий
std::unique_ptr<PaymentStrategy> createPaymentStrategy(const std::string& method);

#endif