#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include <string>
#include <vector>

struct Sale {
    int sale_id;
    std::string sale_date;
    int product_id;
    int customer_id;
    int quantity;
    double amount;
};

struct Product {
    int product_id;
    std::string product_name;
    std::string category;
    double price;
};

struct Customer {
    int customer_id;
    std::string customer_name;
    std::string region;
};

// Функции для загрузки данных из CSV
std::vector<Sale> loadSalesData(const std::string& filename);
std::vector<Product> loadProductsData(const std::string& filename);
std::vector<Customer> loadCustomersData(const std::string& filename);

#endif // CSV_LOADER_H