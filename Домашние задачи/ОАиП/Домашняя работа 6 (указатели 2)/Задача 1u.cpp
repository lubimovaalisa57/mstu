#include <iostream>

// Функция для обмена указателей
void swapPointers(int **a, int **b) 
{
    int *temp = *a;
    *a = *b;
    *b = temp;
}

int main() 
{
    // Создаем переменные
    int x = 10;
    int y = 20;
    
    // Объявляем указатели
    int *p1 = &x;
    int *p2 = &y;
    
    std::cout << "ДО обмена указателей:" << std::endl;
    std::cout << "p1: адрес = " << p1 << ", значение = " << *p1 << " (указывает на x)" << std::endl;
    std::cout << "p2: адрес = " << p2 << ", значение = " << *p2 << " (указывает на y)" << std::endl;
    std::cout << "x = " << x << ", y = " << y << std::endl;
    
    // Вызываем функцию обмена указателей
    swapPointers(&p1, &p2);
    
    std::cout << "ПОСЛЕ обмена указателей: " << std::endl;
    std::cout << "p1: адрес = " << p1 << ", значение = " << *p1 << " (теперь указывает на y)" << std::endl;
    std::cout << "p2: адрес = " << p2 << ", значение = " << *p2 << " (теперь указывает на x)" << std::endl;
    std::cout << "x = " << x << ", y = " << y << std::endl;
    
    return 0;
}