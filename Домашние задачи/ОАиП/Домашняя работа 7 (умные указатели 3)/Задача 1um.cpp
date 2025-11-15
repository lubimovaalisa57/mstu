#include <iostream>
#include <memory>

int main() {
    // Создаем умный указатель и выделяем память с помощью make_unique
    std::unique_ptr<int> ptr = std::make_unique<int>(10);
    
    std::cout << "Исходное значение: " << *ptr << std::endl;
    
    // Изменяем значение на 25
    *ptr = 25;
    
    std::cout << "Измененное значение: " << *ptr << std::endl;
    
    return 0;
}