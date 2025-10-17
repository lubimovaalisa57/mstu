#include <iostream>
#include <vector>
#include <algorithm>

int main() {
   std::vector<int> numbers(10);
    
    std::cout << "Введите 10 элементов вектора: ";
    for (int i = 0; i < 10; ++i) {
        std::cin >> numbers[i];
    }
    
    std::cout << "Исходный вектор: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    std::for_each(numbers.begin(), numbers.end(), [](int &n) {
        n *= 2; 
    });
    
    std::cout << "Удвоенный вектор: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}