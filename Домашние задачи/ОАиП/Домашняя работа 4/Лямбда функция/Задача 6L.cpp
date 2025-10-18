#include <iostream>
#include <vector>
#include <algorithm>

int main() 
{
    std::vector<int> numbers(20);
    std::cout << "Введите 20 чисел: ";
    for (int i = 0; i < 20; ++i) {
        std::cin >> numbers[i];
    }
    
    // Проверяем, есть ли число 7
    auto it = std::find(numbers.begin(), numbers.end(), 7);
    if (it != numbers.end()) {
        std::cout << "Число 7 найдено в векторе" << std::endl;
    } else {
        std::cout << "Число 7 не найдено в векторе" << std::endl;
    }
    
    // Удаляем все повторяющиеся числа
    std::sort(numbers.begin(), numbers.end());
    auto last = std::unique(numbers.begin(), numbers.end());
    numbers.erase(last, numbers.end());
    
    // Выводим оставшиеся элементы
    std::cout << "Уникальные элементы после удаления повторов: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}