#include <iostream>
#include <memory>

int main() 
{
    // Создаем shared_ptr и выделяем память со значением 100
    std::shared_ptr<int> ptr1 = std::make_shared<int>(100);
    
    std::cout << "После создания ptr1:" << std::endl;
    std::cout << "Значение ptr1: " << *ptr1 << std::endl;
    std::cout << "use_count(): " << ptr1.use_count() << std::endl;
    std::cout << "Адрес: " << ptr1.get() << std::endl;
    
    // Создаем копию ptr2
    std::shared_ptr<int> ptr2 = ptr1;
    
    std::cout << "После создания ptr2 (копия ptr1):" << std::endl;
    std::cout << "Значение ptr2: " << *ptr2 << std::endl;
    std::cout << "use_count(): " << ptr1.use_count() << std::endl;
    std::cout << "Адрес ptr1: " << ptr1.get() << std::endl;
    std::cout << "Адрес ptr2: " << ptr2.get() << std::endl;
    
    // Создаем еще одну копию ptr3
    std::shared_ptr<int> ptr3 = ptr2;
    
    std::cout << "После создания ptr3 (копия ptr2):" << std::endl;
    std::cout << "Значение ptr3: " << *ptr3 << std::endl;
    std::cout << "use_count(): " << ptr1.use_count() << std::endl;
    std::cout << "Адрес ptr1: " << ptr1.get() << std::endl;
    std::cout << "Адрес ptr2: " << ptr2.get() << std::endl;
    std::cout << "Адрес ptr3: " << ptr3.get() << std::endl;
    
    // Проверяем метод unique()
    std::cout << "Проверка метода unique():" << std::endl;
    std::cout << "ptr1.unique(): " << std::boolalpha << ptr1.unique() << std::endl;
    std::cout << "ptr2.unique(): " << std::boolalpha << ptr2.unique() << std::endl;
    std::cout << "ptr3.unique(): " << std::boolalpha << ptr3.unique() << std::endl;
    
    // Уничтожаем одну из копий (ptr2)
    {
        std::cout << "--- Вход во внутренний блок ---" << std::endl;
        std::shared_ptr<int> ptr2_local = ptr1;  // Создаем временную копию
        std::cout << "use_count() после создания ptr2_local: " << ptr1.use_count() << std::endl;
        
        // ptr2_local автоматически уничтожится при выходе из блока
    }
    
    std::cout << "После выхода из внутреннего блока (ptr2_local уничтожен):" << std::endl;
    std::cout << "use_count(): " << ptr1.use_count() << std::endl;
    
    // Явно уничтожаем ptr2 с помощью reset()
    std::cout << "--- Явно уничтожаем ptr2 ---" << std::endl;
    ptr2.reset();
    
    std::cout << "После ptr2.reset():" << std::endl;
    std::cout << "use_count(): " << ptr1.use_count() << std::endl;
    std::cout << "ptr2 is nullptr: " << (ptr2 == nullptr) << std::endl;
    std::cout << "Значение ptr1: " << *ptr1 << std::endl;
    std::cout << "Значение ptr3: " << *ptr3 << std::endl;
    
    // Проверяем unique() снова
    std::cout << "Финальная проверка unique():" << std::endl;
    std::cout << "ptr1.unique(): " << std::boolalpha << ptr1.unique() << std::endl;
    std::cout << "ptr3.unique(): " << std::boolalpha << ptr3.unique() << std::endl;
    
    return 0;
}