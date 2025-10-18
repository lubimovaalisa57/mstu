#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() 
{
    std::vector<double> amplitudes(50);
    std::cout << "Введите 50 значений амплитуд вибрации: ";
    for (int i = 0; i < 50; ++i) {
        std::cin >> amplitudes[i];
    }
    
    // Удаляем шумы (значения < 0.1)
    amplitudes.erase(
        std::remove_if(amplitudes.begin(), amplitudes.end(), 
                      [](double a) { return a < 0.1; }),
        amplitudes.end()
    );
    
    // Среднее значение амплитуды
    double average = std::accumulate(amplitudes.begin(), amplitudes.end(), 0.0) / amplitudes.size();
    
    // Максимальное значение амплитуды
    auto max_it = std::max_element(amplitudes.begin(), amplitudes.end());
    
    // Проверяем, превышают ли все значения порог 0.5
    bool all_above_threshold = std::all_of(amplitudes.begin(), amplitudes.end(), 
                                          [](double a) { return a > 0.5; });
    
    // 10 наибольших амплитуд
    std::vector<double> sorted_amplitudes = amplitudes;
    std::sort(sorted_amplitudes.begin(), sorted_amplitudes.end(), std::greater<double>());
    
    std::cout << "Среднее значение амплитуды: " << average << std::endl;
    std::cout << "Максимальное значение амплитуды: " << *max_it << std::endl;
    
    if (all_above_threshold == true) {
        std::cout << "Все значения превышают порог 0.5" << std::endl;
    } 
    else {
        std::cout << "Не все значения превышают порог 0.5" << std::endl;
    }
    
    std::cout << "10 наибольших амплитуд: ";
    for (int i = 0; i < 10 && i < sorted_amplitudes.size(); ++i) {
        std::cout << sorted_amplitudes[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}