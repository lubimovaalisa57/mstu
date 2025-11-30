#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
    
    // Пропускаем заголовок
    std::getline(file, line);
    
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
    
    // Вывод товаров и подсчет статистики
    int totalQuantity = 0;
    double totalValue = 0;
    double maxPrice = 0;
    double minPrice = 100000;
    std::string expensiveProduct, cheapProduct;
    
    for (const auto& p : products) {
        std::cout << p.id << " " << p.name << " " << p.category 
                  << " " << p.price << " " << p.quantity << std::endl;
        
        totalQuantity += p.quantity;
        totalValue += p.price * p.quantity;
        
        if (p.price > maxPrice) {
            maxPrice = p.price;
            expensiveProduct = p.name;
        }
        if (p.price < minPrice) {
            minPrice = p.price;
            cheapProduct = p.name;
        }
    }
    
    std::cout << "Всего товаров: " << totalQuantity << std::endl;
    std::cout << "Общая стоимость: " << totalValue << std::endl;
    std::cout << "Самый дорогой: " << expensiveProduct << " (" << maxPrice << ")" << std::endl;
    std::cout << "Самый дешевый: " << cheapProduct << " (" << minPrice << ")" << std::endl;
    
    return 0;
}