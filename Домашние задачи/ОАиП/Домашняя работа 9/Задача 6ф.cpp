#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main() 
{
    std::ofstream file("products.csv");
    
    file << "id,name,category,price,quantity\n";
    
    std::string categories[] = {"Электроника", "Аксессуары", "Одежда", "Книги", "Спорт"};
    std::string products[] = {"Ноутбук", "Мышь", "Телефон", "Наушники", "Клавиатура", 
                             "Футболка", "Книга", "Мяч", "Часы", "Рюкзак"};
    
    srand(time(0));
    
    for (int i = 1; i <= 20; i++) {
        std::string name = products[rand() % 10] + " " + std::to_string(i);
        std::string category = categories[rand() % 5];
        double price = 100 + rand() % 9900;
        int quantity = 1 + rand() % 100;
        
        file << i << "," << name << "," << category << "," << price << "," << quantity << "\n";
    }
    
    file.close();
    return 0;
}
