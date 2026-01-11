#include <iostream>
#include <memory>
#include <string>
#include "../include/DatabaseConnection.h"
#include "../include/Admin.h"
#include "../include/Manager.h"
#include "../include/Customer.h"

std::shared_ptr<User> login(std::shared_ptr<DatabaseConnection<std::string>> db) {
    std::cout << "Выберите роль:\n";
    std::cout << "1. Администратор\n";
    std::cout << "2. Менеджер\n";
    std::cout << "3. Покупатель\n";
    std::cout << "0. Выход\n";
    std::cout << "Выбор: ";

    int choice;
    std::cin >> choice;

    switch(choice) {
        case 1:
            return std::make_shared<Admin>(1, "Администратор", "admin@store.com", db);
        case 2:
            return std::make_shared<Manager>(2, "Менеджер", "manager@store.com", db);
        case 3:
            return std::make_shared<Customer>(3, "Покупатель", "customer@store.com", db);
        case 0:
            return nullptr;
        default:
            std::cout << "Неверный выбор\n";
            return nullptr;
    }
}

int main() {
    std::cout << "=== ИНТЕРНЕТ-МАГАЗИН ===\n";

    std::string connection_string = "host=localhost port=5432 user=postgres dbname=online_store";

    auto db = std::make_shared<DatabaseConnection<std::string>>(connection_string);

    if (!db->isConnected()) {
        std::cout << "Ошибка подключения к базе данных\n";
        std::cout << "Проверьте:\n";
        std::cout << "1. Запущен ли PostgreSQL\n";
        std::cout << "2. Существует ли база данных 'online_store'\n";
        std::cout << "3. Параметры подключения: " << connection_string << "\n";
        return 1;
    }

    std::cout << "Подключено к базе данных\n";

    auto user = login(db);
    if (!user) return 0;

    std::cout << "Добро пожаловать, " << user->getName() << "!\n";

    while(true) {
        user->showMenu();
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Выход из системы\n";
            break;
        }
        user->performAction(choice);
    }

    return 0;
}