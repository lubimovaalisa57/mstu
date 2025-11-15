#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

int main() 
{
    std::vector<std::string> routes = {
        "Moscow-Berlin",
        "Berlin-Paris",
        "Paris-Rome",
        "Rome-Moscow"
    };
    
    auto ptrRoutes = std::make_shared<std::vector<std::string>>(routes);
    
    // Лямбда для подсчета маршрутов с городом
    auto countCity = [](std::shared_ptr<std::vector<std::string>> routes, const std::string& city) -> int {
        int count = 0;
        for (const auto& route : *routes) {
            if (route.find(city) != std::string::npos) count++;
        }
        return count;
    };
    
    // Лямбда для сортировки по длине (убывание)
    auto sortByLength = [](std::shared_ptr<std::vector<std::string>> routes) {
        std::sort(routes->begin(), routes->end(),
            [](const std::string& a, const std::string& b) {
                return a.length() > b.length();
            });
    };
    
    // Лямбда для объединения маршрутов
    auto concat = [](std::shared_ptr<std::vector<std::string>> routes) -> std::string {
        std::string result;
        for (size_t i = 0; i < routes->size(); i++) {
            result += (*routes)[i];
            if (i < routes->size() - 1) result += " -> ";
        }
        return result;
    };
    
    // Выполнение операций
    int parisCount = countCity(ptrRoutes, "Paris");
    std::cout << "Количество маршрутов с \"Paris\": " << parisCount << std::endl;
    
    sortByLength(ptrRoutes);
    std::cout << "Отсортированные маршруты:" << std::endl;
    for (const auto& route : *ptrRoutes) {
        std::cout << route << std::endl;
    }
    
    std::string combined = concat(ptrRoutes);
    std::cout << "Общий маршрут:" << std::endl << combined << std::endl;
    
    return 0;
}