#include <iostream>
#include "csv_loader.h"
#include "database.h"

int main() {
    try {
        // 1. Загрузка данных из CSV
        std::cout << "Загрузка данных из CSV файлов..." << std::endl;

        auto sales = loadSalesData("../data/sales.csv");
        auto products = loadProductsData("../data/products.csv");
        auto customers = loadCustomersData("../data/customers.csv");

        std::cout << "Загружено записей:" << std::endl;
        std::cout << "- Продажи: " << sales.size() << std::endl;
        std::cout << "- Товары: " << products.size() << std::endl;
        std::cout << "- Клиенты: " << customers.size() << std::endl;

        // 2. Подключение к базе данных
        std::string conninfo = "host=localhost port=5432 dbname=dwh_db user=postgres";
        Database db(conninfo);

        if (!db.connect()) {
            std::cerr << "Не удалось подключиться к базе данных!" << std::endl;
            return 1;
        }

        // 3. Создание таблиц
        std::cout << "\nСоздание таблиц..." << std::endl;
        db.createTables();

        // 4. Загрузка данных в базу
        std::cout << "\nЗагрузка данных в базу..." << std::endl;
        db.insertProducts(products);
        db.insertCustomers(customers);
        db.insertSales(sales);

        // 5. Создание индексов
        std::cout << "\nСоздание индексов..." << std::endl;
        db.createIndexes();

        // 6. Выполнение аналитических запросов
        std::cout << "\nВыполнение аналитических запросов..." << std::endl;
        db.executeAnalytics();

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nПрограмма успешно завершена!" << std::endl;
    return 0;
}