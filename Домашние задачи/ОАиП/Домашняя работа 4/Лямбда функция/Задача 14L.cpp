#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() 
{
    std::vector<double> consumption(24);
    std::cout << "Введите потребление энергии за 24 часа (100-500 кВт·ч): ";
    for (int i = 0; i < 24; ++i) {
        std::cin >> consumption[i];
    }
    
    // Суммарное потребление
    double total = std::accumulate(consumption.begin(), consumption.end(), 0.0);
    
    // Среднее потребление
    double average = total / consumption.size();
    
    // Час пикового потребления
    auto max_it = std::max_element(consumption.begin(), consumption.end());
    
    std::cout << "Суммарное потребление: " << total << " кВт·ч" << std::endl;
    std::cout << "Среднее потребление: " << average << " кВт·ч" << std::endl;
    std::cout << "Пиковое потребление: " << *max_it << " кВт·ч в час " << std::endl;
    
    // Отклонение каждого часа от среднего
    std::vector<double> deviations(24);
    std::transform(consumption.begin(), consumption.end(), deviations.begin(),
                  [average](double hour) { return hour - average; });
    
    std::cout << "Отклонения от среднего: ";
    for (const auto& dev : deviations) {
        std::cout << dev << " ";
    }
    std::cout << std::endl;
    
    // Топ-5 минимальных часов потребления
    std::vector<double> sorted_consumption = consumption;
    std::sort(sorted_consumption.begin(), sorted_consumption.end());
    
    std::cout << "Топ-5 минимальных часов потребления: ";
    for (int i = 0; i < 5 && i < sorted_consumption.size(); ++i) {
        std::cout << sorted_consumption[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}