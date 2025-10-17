#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers(10);
    
    std::cout << "Введите 10 элементов вектора: ";
    for (int i = 0; i < 10; ++i) {
        std::cin >> numbers[i];
    }
    
    auto new_end = std::remove_if(numbers.begin(), numbers.end(), [](int n) {
        return n < 0;
    });
    
    numbers.erase(new_end, numbers.end());
    
    std::cout << "Вектор после удаления отрицательных чисел: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}