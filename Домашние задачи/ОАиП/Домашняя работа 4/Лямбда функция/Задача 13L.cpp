#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() 
{
    std::vector<double> pressure(50);
    std::cout << "Введите 50 измерений давления (1-10 бар): ";
    for (int i = 0; i < 50; ++i) {
        std::cin >> pressure[i];
    }
    
    // Удаляем ошибочные значения (< 0 или > 12)
    pressure.erase(
        std::remove_if(pressure.begin(), pressure.end(), 
                      [](double p) { return p < 0 || p > 12; }),
        pressure.end()
    );
    
    // Среднее давление
    double average = std::accumulate(pressure.begin(), pressure.end(), 0.0) / pressure.size();
    
    // Минимальное давление
    auto min_it = std::min_element(pressure.begin(), pressure.end());
    
    // Максимальное давление
    auto max_it = std::max_element(pressure.begin(), pressure.end());
    
    std::cout << "Среднее давление: " << average << std::endl;
    std::cout << "Минимальное давление: " << *min_it << std::endl;
    std::cout << "Максимальное давление: " << *max_it << std::endl;
    std::cout << "Значения, превышающие 8 бар: ";
    std::for_each(pressure.begin(), pressure.end(),
                 [](double p) { 
                     if (p > 8) {
                         std::cout << p << " ";
                     }
                 });
    std::cout << std::endl;
    
    return 0;
}