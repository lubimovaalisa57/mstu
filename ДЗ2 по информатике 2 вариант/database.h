#ifndef DATABASE_H
#define DATABASE_H

#include <libpq-fe.h>
#include <string>
#include <vector>
#include "csv_loader.h"

class Database {
private:
    PGconn* connection;

public:
    Database(const std::string& conninfo);
    ~Database();

    bool connect();
    void disconnect();

    // Создание таблиц
    void createTables();

    // Вставка данных
    void insertSales(const std::vector<Sale>& sales);
    void insertProducts(const std::vector<Product>& products);
    void insertCustomers(const std::vector<Customer>& customers);

    // Создание индексов
    void createIndexes();

    // Выполнение аналитических запросов
    void executeAnalytics();
};

#endif // DATABASE_H