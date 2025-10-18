#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() 
{
    std::vector<double> temperatures;
    int n;
    std::cout << "Введите количество температур: ";
    std::cin >> n;
    std::cout << "Введите " << n << " температур: ";
    for (int i = 0; i < n; ++i) {
        double temp;
        std::cin >> temp;
        temperatures.push_back(temp);
    }
    
    // Удаляем значения вне диапазона [-50, 50]
    temperatures.erase(
        std::remove_if(temperatures.begin(), temperatures.end(), 
                      [](double temp) { return temp < -50 || temp > 50; }),
        temperatures.end()
    );
    
    // Находим минимальную температуру
    double min_temp = temperatures[0];
    for (size_t i = 1; i < temperatures.size(); ++i) {
        if (temperatures[i] < min_temp) {
            min_temp = temperatures[i];
        }
    }
    
    // Находим максимальную температуру
    double max_temp = temperatures[0];
    for (size_t i = 1; i < temperatures.size(); ++i) {
        if (temperatures[i] > max_temp) {
            max_temp = temperatures[i];
        }
    }
    
    // Считаем среднюю температуру
    double sum = std::accumulate(temperatures.begin(), temperatures.end(), 0.0);
    double average_temp = sum / temperatures.size();
    
    // Проверяем, превышают ли все температуры -10 градусов
    bool all_above_minus_10 = true;
    for (const auto& temp : temperatures) {
        if (temp <= -10) {
            all_above_minus_10 = false;
            break;
        }
    }
    
    // Выводим результаты
    std::cout << "Температуры в диапазоне [-50, 50]: ";
    for (const auto& temp : temperatures) {
        std::cout << temp << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Минимальная температура: " << min_temp << std::endl;
    std::cout << "Максимальная температура: " << max_temp << std::endl;
    std::cout << "Средняя температура: " << average_temp << std::endl;
    
    if (all_above_minus_10 == true) {
        std::cout << "Все температуры превышают -10 градусов" << std::endl;
    } 
    else {
        std::cout << "Не все температуры превышают -10 градусов" << std::endl;
    }
    
    return 0;
}