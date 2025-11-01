#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    int* p = &vec[0];
    
    int sum = 0;
    for (size_t i = 0; i < vec.size(); i++) {
        sum += *(p + i);
    }

    std::cout << "Сумма элементов: " << sum << std::endl;
    
    return 0;
}