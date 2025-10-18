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
    
    auto minmax = std::minmax_element(numbers.begin(), numbers.end());
    std::cout << "Минимальное значение: " << *minmax.first << std::endl;
    std::cout << "Максимальное значение: " << *minmax.second << std::endl;
    
    double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0);
    double average = sum / numbers.size();
    std::cout << "Среднее значение: " << average << std::endl;
    
    std::vector<double> sorted_numbers = numbers;
    std::sort(sorted_numbers.begin(), sorted_numbers.end());
    
    double median;
    if (sorted_numbers.size() % 2 == 0) {
        median = (sorted_numbers[sorted_numbers.size()/2 - 1] + 
                 sorted_numbers[sorted_numbers.size()/2]) / 2.0;
    } else {
        median = sorted_numbers[sorted_numbers.size()/2];
    }
    
    std::cout << "Медиана: " << median << std::endl;
    
    return 0;
}