#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct Product 
{
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;
};

int main() 
{
    std::ifstream file("products.csv");
    std::string line;
    std::vector<Product> products;
    
    std::getline(file, line); // заголовок
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Product p;
        
        std::getline(ss, token, ',');
        p.id = std::stoi(token);
        std::getline(ss, p.name, ',');
        std::getline(ss, p.category, ',');
        std::getline(ss, token, ',');
        p.price = std::stod(token);
        std::getline(ss, token, ',');
        p.quantity = std::stoi(token);
        
        products.push_back(p);
    }
    file.close();
    
    // Фильтры
    auto expensive_filter = [](const Product& p) { return p.price > 5000; };
    auto electronics_filter = [](const Product& p) { return p.category == "Электроника"; };
    auto in_stock_filter = [](const Product& p) { return p.quantity > 10; };
    
    // Применяем фильтры
    std::vector<Product> filtered;
    std::copy_if(products.begin(), products.end(), std::back_inserter(filtered), expensive_filter);
    
    // Сохраняем отфильтрованные данные
    std::ofstream out("filtered_products.csv");
    out << "id,name,category,price,quantity\n";
    
    for (const auto& p : filtered) {
        out << p.id << "," << p.name << "," << p.category << "," << p.price << "," << p.quantity << "\n";
    }
    out.close();
    
    std::cout << "Отфильтровано товаров: " << filtered.size() << std::endl;
    
    return 0;
}