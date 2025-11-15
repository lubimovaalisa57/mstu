#include <iostream>
#include <memory>

int main() 
{
    std::shared_ptr<int> ptr1 = std::make_shared<int>(100);
    std::cout << ptr1.use_count() << std::endl;  // Счетчик: 1
    
    std::shared_ptr<int> ptr2 = ptr1;  // Копирование
    std::cout << ptr1.use_count() << std::endl;  // Счетчик: 2
    
    std::shared_ptr<int> ptr3 = ptr2;  // Еще копия
    std::cout << ptr1.use_count() << std::endl;  // Счетчик: 3
    
    ptr2.reset();  // Уничтожение одной копии
    std::cout << ptr1.use_count() << std::endl;  // Счетчик: 2
    return 0;
}