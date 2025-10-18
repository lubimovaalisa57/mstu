#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() 
{
    std::vector<double> numbers(20);
    std::cout << "Введите 20 чисел: ";
    for (int i = 0; i < 20; ++i) {
        std::cin >> numbers[i];
    }
    
    // Находим минимальное число
    double min_value = numbers[0];
    for (int i = 1; i < 20; ++i) {
        if (numbers[i] < min_value) {
            min_value = numbers[i];
        }
    }
    
    // Находим максимальное число
    double max_value = numbers[0];
    for (int i = 1; i < 20; ++i) {
        if (numbers[i] > max_value) {
            max_value = numbers[i];
        }
    }
    
    // Считаем среднее значение
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
    double average = sum / numbers.size();
    
    // Находим медиану
    std::vector<double> sorted_numbers = numbers;
    std::sort(sorted_numbers.begin(), sorted_numbers.end());
    
    double median;
    if (sorted_numbers.size() % 2 == 0) {
        median = (sorted_numbers[sorted_numbers.size()/2 - 1] + 
                 sorted_numbers[sorted_numbers.size()/2]) / 2.0;
    } else {
        median = sorted_numbers[sorted_numbers.size()/2];
    }
    
    // Выводим результаты
    std::cout << "Минимальное число: " << min_value << std::endl;
    std::cout << "Максимальное число: " << max_value << std::endl;
    std::cout << "Среднее значение: " << average << std::endl;
    std::cout << "Медиана: " << median << std::endl;
    
    return 0;
}