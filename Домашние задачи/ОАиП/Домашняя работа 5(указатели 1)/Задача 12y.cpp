#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    int* ptr = numbers.data();
    
    for (size_t i = 0; i < numbers.size(); i++) {
        *(ptr + i) += 10;
    }
    
    std::cout << "Результат: ";
    for (size_t i = 0; i < numbers.size(); i++) {
        std::cout << *(ptr + i) << " ";
    }
    std::cout << std::endl;
    
    return 0;
}