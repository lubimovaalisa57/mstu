#include "csv_loader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<Sale> loadSalesData(const std::string& filename) {
    std::vector<Sale> sales;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла " << filename << std::endl;
        return sales;
    }

    std::string line;
    // Пропускаем заголовок, если есть
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Sale sale;
        std::string temp;

        try {
            std::getline(ss, temp, ',');
            sale.sale_id = std::stoi(temp);

            std::getline(ss, sale.sale_date, ',');

            std::getline(ss, temp, ',');
            sale.product_id = std::stoi(temp);

            std::getline(ss, temp, ',');
            sale.customer_id = std::stoi(temp);

            std::getline(ss, temp, ',');
            sale.quantity = std::stoi(temp);

            std::getline(ss, temp, ',');
            sale.amount = std::stod(temp);

            sales.push_back(sale);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при обработке строки: " << line << std::endl;
        }
    }

    file.close();
    return sales;
}

std::vector<Product> loadProductsData(const std::string& filename) {
    std::vector<Product> products;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла " << filename << std::endl;
        return products;
    }

    std::string line;
    std::getline(file, line); // Пропускаем заголовок

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Product product;
        std::string temp;

        try {
            std::getline(ss, temp, ',');
            product.product_id = std::stoi(temp);

            std::getline(ss, product.product_name, ',');
            std::getline(ss, product.category, ',');

            std::getline(ss, temp, ',');
            product.price = std::stod(temp);

            products.push_back(product);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при обработке строки: " << line << std::endl;
        }
    }

    file.close();
    return products;
}

std::vector<Customer> loadCustomersData(const std::string& filename) {
    std::vector<Customer> customers;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла " << filename << std::endl;
        return customers;
    }

    std::string line;
    std::getline(file, line); // Пропускаем заголовок

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Customer customer;
        std::string temp;

        try {
            std::getline(ss, temp, ',');
            customer.customer_id = std::stoi(temp);

            std::getline(ss, customer.customer_name, ',');
            std::getline(ss, customer.region, ',');

            customers.push_back(customer);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка при обработке строки: " << line << std::endl;
        }
    }

    file.close();
    return customers;
}