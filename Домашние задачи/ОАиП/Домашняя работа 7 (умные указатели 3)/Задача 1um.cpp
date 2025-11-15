#include <iostream>
#include <memory>

int main() 
{
    std::unique_ptr<int> ptr = std::make_unique<int>(10);  // Создание
    std::cout << *ptr << std::endl;  // Вывод значения
    *ptr = 25;  // Изменение значения
    std::cout << *ptr << std::endl;
    return 0;
}