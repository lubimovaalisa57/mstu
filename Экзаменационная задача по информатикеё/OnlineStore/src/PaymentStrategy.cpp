#include "../include/PaymentStrategy.h"
#include <iostream>

bool CreditCardPayment::pay(double amount) {
    std::cout << "Оплата банковской картой\n";
    std::cout << "Сумма: " << amount << "\n";

    std::cout << "Введите номер карты (16 цифр): ";
    std::string card_number;
    std::cin >> card_number;

    std::cout << "Введите срок действия (ММ/ГГ): ";
    std::string expiry_date;
    std::cin >> expiry_date;

    std::cout << "Введите CVV: ";
    std::string cvv;
    std::cin >> cvv;

    if (card_number.length() == 16 && cvv.length() == 3) {
        std::cout << "Платеж обработан\n";
        return true;
    } else {
        std::cout << "Неверные данные карты\n";
        return false;
    }
}

std::string CreditCardPayment::getName() const {
    return "Карта";
}

bool EWalletPayment::pay(double amount) {
    std::cout << "Оплата электронным кошельком\n";
    std::cout << "Сумма: " << amount << "\n";

    std::cout << "Введите номер кошелька: ";
    std::string wallet_number;
    std::cin >> wallet_number;

    if (!wallet_number.empty()) {
        std::cout << "Платеж обработан\n";
        return true;
    } else {
        std::cout << "Неверный номер кошелька\n";
        return false;
    }
}

std::string EWalletPayment::getName() const {
    return "Кошелек";
}

bool SBPPayment::pay(double amount) {
    std::cout << "Оплата через СБП\n";
    std::cout << "Сумма: " << amount << "\n";
    std::cout << "Для оплаты через СБП:\n";
    std::cout << "1. Откройте приложение банка\n";
    std::cout << "2. Выберите оплату по QR-коду\n";
    std::cout << "3. Отсканируйте код\n";
    std::cout << "4. Подтвердите платеж\n\n";

    std::cout << "Введите 'да' после подтверждения платежа: ";
    std::string confirmation;
    std::cin >> confirmation;

    return confirmation == "да" || confirmation == "yes";
}

std::string SBPPayment::getName() const {
    return "СБП";
}