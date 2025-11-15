#include <iostream>
#include <memory>

int main() 
{
    std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
    std::unique_ptr<int> ptr2 = std::move(ptr1);  // Передача владения
    
    std::cout << (ptr1 == nullptr) << std::endl;  // Проверка ptr1
    std::cout << *ptr2 << std::endl;  // Проверка ptr2
    return 0;
}