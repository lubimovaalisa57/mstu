#include <iostream>
#include <memory>

int main() 
{
    // Создаем умный указатель и выделяем память со значением 42
    std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
    
    // Выводим исходное значение ptr1
    std::cout << "Исходное значение ptr1: " << *ptr1 << std::endl;
    std::cout << "Адрес ptr1: " << ptr1.get() << std::endl;
    
    // Передаем владение из ptr1 в ptr2
    std::unique_ptr<int> ptr2 = std::move(ptr1);
    
    std::cout << "После передачи  " << std::endl;
    
    if (ptr1 == nullptr) {
        std::cout << "ptr1 теперь nullptr" << std::endl;
    } 
    else {
        std::cout << "ptr1 все еще указывает на значение: " << *ptr1 << std::endl;
    }
    std::cout << "Адрес ptr1: " << ptr1.get() << std::endl;
    
    // Проверяем состояние ptr2 (должен хранить значение 42)
    if (ptr2) {
        std::cout << "ptr2 хранит значение: " << *ptr2 << std::endl;
    } 
    else {
        std::cout << "ptr2 является nullptr" << std::endl;
    }
    std::cout << "Адрес ptr2: " << ptr2.get() << std::endl;
    
    return 0;
}