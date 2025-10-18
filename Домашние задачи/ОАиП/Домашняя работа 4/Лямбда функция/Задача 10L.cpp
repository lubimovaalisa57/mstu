#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() 
{
    std::vector<double> consumption(30);
    std::cout << "Введите потребление энергии за 30 дней (кВт·ч): ";
    for (int i = 0; i < 30; ++i) {
        std::cin >> consumption[i];
    }
    
    // Общее потребление за месяц
    double total = std::accumulate(consumption.begin(), consumption.end(), 0.0);
    
    // Среднесуточное потребление
    double average = total / consumption.size();
    
    // Минимальное потребление
    auto min_it = std::min_element(consumption.begin(), consumption.end());
    
    // Максимальное потребление
    auto max_it = std::max_element(consumption.begin(), consumption.end());
    
    // Пиковые дни (потребление > среднего на 20%)
    double threshold = average * 1.2;
    std::vector<double> peak_days;
    std::copy_if(consumption.begin(), consumption.end(), 
                std::back_inserter(peak_days),
                [threshold](double day) { return day > threshold; });
    
    std::cout << "Общее потребление за месяц: " << total << " кВт·ч" << std::endl;
    std::cout << "Среднесуточное потребление: " << average << " кВт·ч" << std::endl;
    std::cout << "Минимальное потребление: " << *min_it << " кВт·ч" << std::endl;
    std::cout << "Максимальное потребление: " << *max_it << " кВт·ч" << std::endl;
    std::cout << "Пиковые дни (>" << threshold << " кВт·ч): ";
    for (const auto& day : peak_days) {
        std::cout << day << " ";
    }
    std::cout << std::endl;
    
    return 0;
}