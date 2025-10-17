#include <iostream>
#include <vector>
#include <algorithm>

int main() 
{
    std::vector<int> numbers(10);
    
    for (int i = 0; i < 10; ++i) {
        numbers[i] = i + 1;
    }
    
    std::cout << "Элементы вектора: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n) {
        std::cout << n << " ";
    });
    std::cout << std::endl;
    
    return 0;
}