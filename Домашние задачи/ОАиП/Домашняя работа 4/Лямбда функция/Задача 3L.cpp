#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers(20);
    
    std::cout << "Введите 20 элементов вектора: ";
    for (int i = 0; i < 20; ++i) {
        std::cin >> numbers[i];
    }
    
    auto max_it = std::max_element(numbers.begin(), numbers.end());
    
    std::cout << "Максимальный элемент: " << *max_it << std::endl;
    
    return 0;
}