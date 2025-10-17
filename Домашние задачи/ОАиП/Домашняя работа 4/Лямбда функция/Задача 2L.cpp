#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers(10);
    
    for (int i = 0; i < 10; ++i) {
        numbers[i] = i + 1;
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