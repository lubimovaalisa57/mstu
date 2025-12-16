#include "database.h"
#include "date_converter.h"
#include <iostream>
#include <iomanip>

Database::Database(const std::string& conninfo) {
    connection = PQconnectdb(conninfo.c_str());

    if (PQstatus(connection) != CONNECTION_OK) {
        std::cerr << "Ошибка подключения: " << PQerrorMessage(connection) << std::endl;
    } else {
        std::cout << "Подключение к базе данных успешно!" << std::endl;
    }
}

Database::~Database() {
    disconnect();
}

bool Database::connect() {
    return PQstatus(connection) == CONNECTION_OK;
}

void Database::disconnect() {
    if (connection) {
        PQfinish(connection);
        connection = nullptr;
    }
}

void Database::createTables() {
    const char* create_products = R"(
        CREATE TABLE IF NOT EXISTS products_dim (
            product_id INTEGER PRIMARY KEY,
            product_name VARCHAR(255),
            category VARCHAR(100),
            price DECIMAL(10, 2)
        );
    )";

    const char* create_customers = R"(
        CREATE TABLE IF NOT EXISTS customers_dim (
            customer_id INTEGER PRIMARY KEY,
            customer_name VARCHAR(255),
            region VARCHAR(100)
        );
    )";

    const char* create_time = R"(
        CREATE TABLE IF NOT EXISTS time_dim (
            time_id SERIAL PRIMARY KEY,
            date DATE UNIQUE,
            year INTEGER,
            quarter INTEGER,
            month INTEGER,
            day INTEGER,
            day_of_week VARCHAR(20)
        );
    )";

    const char* create_sales = R"(
        CREATE TABLE IF NOT EXISTS sales_fact (
            sale_id INTEGER PRIMARY KEY,
            sale_date DATE,
            product_id INTEGER REFERENCES products_dim(product_id),
            customer_id INTEGER REFERENCES customers_dim(customer_id),
            quantity INTEGER,
            amount DECIMAL(10, 2)
        );
    )";

    PGresult* res;

    res = PQexec(connection, create_products);
    PQclear(res);

    res = PQexec(connection, create_customers);
    PQclear(res);

    res = PQexec(connection, create_time);
    PQclear(res);

    res = PQexec(connection, create_sales);
    PQclear(res);

    std::cout << "Таблицы созданы успешно!" << std::endl;
}

void Database::insertProducts(const std::vector<Product>& products) {
    for (const auto& product : products) {
        std::string query = "INSERT INTO products_dim (product_id, product_name, category, price) "
                           "VALUES (" + std::to_string(product.product_id) + ", "
                           "'" + product.product_name + "', "
                           "'" + product.category + "', "
                           + std::to_string(product.price) + ") "
                           "ON CONFLICT (product_id) DO NOTHING;";

        PGresult* res = PQexec(connection, query.c_str());
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "Ошибка при вставке product: " << PQerrorMessage(connection) << std::endl;
        }
        PQclear(res);
    }
    std::cout << "Данные products загружены!" << std::endl;
}

void Database::insertCustomers(const std::vector<Customer>& customers) {
    for (const auto& customer : customers) {
        std::string query = "INSERT INTO customers_dim (customer_id, customer_name, region) "
                           "VALUES (" + std::to_string(customer.customer_id) + ", "
                           "'" + customer.customer_name + "', "
                           "'" + customer.region + "') "
                           "ON CONFLICT (customer_id) DO NOTHING;";

        PGresult* res = PQexec(connection, query.c_str());
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "Ошибка при вставке customer: " << PQerrorMessage(connection) << std::endl;
        }
        PQclear(res);
    }
    std::cout << "Данные customers загружены!" << std::endl;
}

void Database::insertSales(const std::vector<Sale>& sales) {
    for (const auto& sale : sales) {
        std::string formatted_date = convertToDateFormat(sale.sale_date);
        if (formatted_date.empty()) continue;

        // Вставляем дату в time_dim
        std::string time_query = "INSERT INTO time_dim (date, year, quarter, month, day, day_of_week) "
                                "SELECT '" + formatted_date + "', "
                                "EXTRACT(YEAR FROM DATE '" + formatted_date + "'), "
                                "EXTRACT(QUARTER FROM DATE '" + formatted_date + "'), "
                                "EXTRACT(MONTH FROM DATE '" + formatted_date + "'), "
                                "EXTRACT(DAY FROM DATE '" + formatted_date + "'), "
                                "TO_CHAR(DATE '" + formatted_date + "', 'Day') "
                                "WHERE NOT EXISTS (SELECT 1 FROM time_dim WHERE date = '" + formatted_date + "');";

        PGresult* res = PQexec(connection, time_query.c_str());
        PQclear(res);

        // Вставляем продажу
        std::string sales_query = "INSERT INTO sales_fact (sale_id, sale_date, product_id, customer_id, quantity, amount) "
                                 "VALUES (" + std::to_string(sale.sale_id) + ", "
                                 "'" + formatted_date + "', "
                                 + std::to_string(sale.product_id) + ", "
                                 + std::to_string(sale.customer_id) + ", "
                                 + std::to_string(sale.quantity) + ", "
                                 + std::to_string(sale.amount) + ") "
                                 "ON CONFLICT (sale_id) DO NOTHING;";

        res = PQexec(connection, sales_query.c_str());
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            std::cerr << "Ошибка при вставке sale: " << PQerrorMessage(connection) << std::endl;
        }
        PQclear(res);
    }
    std::cout << "Данные sales загружены!" << std::endl;
}

void Database::createIndexes() {
    const char* indexes[] = {
        "CREATE INDEX IF NOT EXISTS idx_sales_fact_product ON sales_fact(product_id);",
        "CREATE INDEX IF NOT EXISTS idx_sales_fact_customer ON sales_fact(customer_id);",
        "CREATE INDEX IF NOT EXISTS idx_sales_fact_date ON sales_fact(sale_date);",
        "CREATE INDEX IF NOT EXISTS idx_products_dim_category ON products_dim(category);",
        "CREATE INDEX IF NOT EXISTS idx_customers_dim_region ON customers_dim(region);"
    };

    for (const char* index_query : indexes) {
        PGresult* res = PQexec(connection, index_query);
        PQclear(res);
    }
    std::cout << "Индексы созданы!" << std::endl;
}

void Database::executeAnalytics() {
    // 1. Объем продаж по категориям товаров
    const char* query1 = R"(
        SELECT p.category, SUM(s.amount) AS total_sales
        FROM sales_fact s
        JOIN products_dim p ON s.product_id = p.product_id
        GROUP BY p.category
        ORDER BY total_sales DESC;
    )";

    std::cout << "\n=== Объем продаж по категориям товаров ===" << std::endl;
    PGresult* res = PQexec(connection, query1);

    int rows = PQntuples(res);

    for (int i = 0; i < rows; i++) {
        std::cout << "Категория: " << PQgetvalue(res, i, 0)
                  << ", Продажи: " << PQgetvalue(res, i, 1) << std::endl;
    }
    PQclear(res);

    // 2. Количество покупок по регионам
    const char* query2 = R"(
        SELECT c.region, COUNT(s.sale_id) AS number_of_sales
        FROM sales_fact s
        JOIN customers_dim c ON s.customer_id = c.customer_id
        GROUP BY c.region
        ORDER BY number_of_sales DESC;
    )";

    std::cout << "\n=== Количество покупок по регионам ===" << std::endl;
    res = PQexec(connection, query2);

    rows = PQntuples(res);
    for (int i = 0; i < rows; i++) {
        std::cout << "Регион: " << PQgetvalue(res, i, 0)
                  << ", Количество покупок: " << PQgetvalue(res, i, 1) << std::endl;
    }
    PQclear(res);

    // 3. Средний чек за месяц
    const char* query3 = R"(
        SELECT EXTRACT(YEAR FROM s.sale_date) as year,
               EXTRACT(MONTH FROM s.sale_date) as month,
               AVG(s.amount) AS average_ticket
        FROM sales_fact s
        GROUP BY year, month
        ORDER BY year, month;
    )";

    std::cout << "\n=== Средний чек за месяц ===" << std::endl;
    res = PQexec(connection, query3);

    rows = PQntuples(res);
    for (int i = 0; i < rows; i++) {
        std::cout << "Год: " << PQgetvalue(res, i, 0)
                  << ", Месяц: " << PQgetvalue(res, i, 1)
                  << ", Средний чек: " << PQgetvalue(res, i, 2) << std::endl;
    }
    PQclear(res);
}