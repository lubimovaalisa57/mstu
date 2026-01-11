#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <memory>
#include <functional>

namespace Utils {
    // Лямбда для фильтрации по статусу
    template<typename T>
    inline auto filterByStatus = [](const std::vector<T>& orders, const std::string& status) {
        std::vector<T> result;
        std::copy_if(orders.begin(), orders.end(), std::back_inserter(result),
            [&status](const auto& order) {
                return order->getStatus() == status;
            });
        return result;
    };

    // Лямбда для проверки прав доступа
    inline auto checkPermission = [](const std::string& userRole, const std::string& requiredRole) {
        std::vector<std::string> hierarchy = {"customer", "manager", "admin"};
        auto userPos = std::find(hierarchy.begin(), hierarchy.end(), userRole);
        auto requiredPos = std::find(hierarchy.begin(), hierarchy.end(), requiredRole);
        return userPos != hierarchy.end() && requiredPos != hierarchy.end() &&
               std::distance(hierarchy.begin(), userPos) >= std::distance(hierarchy.begin(), requiredPos);
    };

    // Лямбда для подсчета суммы заказов
    template<typename T>
    inline auto calculateTotal = [](const std::vector<T>& orders) {
        return std::accumulate(orders.begin(), orders.end(), 0.0,
            [](double sum, const auto& order) {
                return sum + order->getTotalPrice();
            });
    };

    // Лямбда для форматирования цены
    inline auto formatPrice = [](double price) -> std::string {
        return std::to_string(price).substr(0, std::to_string(price).find('.') + 3) + " руб.";
    };

    // Функция для безопасного ввода числа
    inline int getIntInput(const std::string& prompt, int min = INT_MIN, int max = INT_MAX) {
        int value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;
            if (std::cin.fail() || value < min || value > max) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Неверный ввод. Пожалуйста, введите число от "
                          << min << " до " << max << "\n";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }
    }

    // Функция для безопасного ввода double
    inline double getDoubleInput(const std::string& prompt, double min = 0.0) {
        double value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;
            if (std::cin.fail() || value < min) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Неверный ввод. Пожалуйста, введите число >= " << min << "\n";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }
    }
}

#endif