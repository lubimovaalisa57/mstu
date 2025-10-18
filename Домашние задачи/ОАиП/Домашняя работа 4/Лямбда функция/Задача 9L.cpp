#include <iostream>
#include <vector>
#include <algorithm>

int main() 
{
    std::vector<double> power(20);
    std::cout << "Введите 20 значений мощности двигателя (кВт): ";
    for (int i = 0; i < 20; ++i) {
        std::cin >> power[i];
    }
    
    // Удаляем отрицательные значения
    power.erase(
        std::remove_if(power.begin(), power.end(), 
                      [](double p) { return p < 0; }),
        power.end()
    );
    
    // Находим минимальную мощность
    auto min_it = std::min_element(power.begin(), power.end());
    
    // Находим максимальную мощность
    auto max_it = std::max_element(power.begin(), power.end());
    
    // Считаем среднюю мощность
    double sum = 0;
    for (const auto& p : power) {
        sum += p;
    }
    double average = sum / power.size();
    
    // Проверяем диапазон 10-90 кВт
    bool in_range = std::all_of(power.begin(), power.end(), 
                               [](double p) { return p >= 10 && p <= 90; });
    
    // Сортируем  по возрастанию
    std::vector<double> sorted_power = power;
    std::sort(sorted_power.begin(), sorted_power.end());
    
    // Находим медиану
    double median;
    if (sorted_power.size() % 2 == 0) {
        median = (sorted_power[sorted_power.size()/2 - 1] + sorted_power[sorted_power.size()/2]) / 2;
    } 
    else {
        median = sorted_power[sorted_power.size()/2];
    }
    
    std::cout << "Минимальная мощность: " << *min_it << " кВт" << std::endl;
    std::cout << "Максимальная мощность: " << *max_it << " кВт" << std::endl;
    std::cout << "Средняя мощность: " << average << " кВт" << std::endl;
    
    if (in_range == true) {
        std::cout << "Двигатель работал в пределах 10-90 кВт" << std::endl;
    } 
    else {
        std::cout << "Двигатель не всегда работал в пределах 10-90 кВт" << std::endl;
    }
    
    std::cout << "Медиана мощности: " << median << " кВт" << std::endl;
    
    return 0;
}