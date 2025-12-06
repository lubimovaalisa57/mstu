#include <iostream>

union Variant 
{
    int i;
    double d;
    char c;
};

int main() 
{
    Variant data;
    char type;
    
    std::cout << "Выберите тип данных (i - целое число, d - число с плавающей запятой, c - символ): ";
    std::cin >> type;
    
    if (type == 'i') {
        std::cout << "Введите целое число: ";
        std::cin >> data.i;
        std::cout << "Значение: " << data.i << std::endl;
    }
    else if (type == 'd') {
        std::cout << "Введите число с плавающей запятой: ";
        std::cin >> data.d;
        std::cout << "Значение: " << data.d << std::endl;
    }
    else if (type == 'c') {
        std::cout << "Введите символ: ";
        std::cin >> data.c;
        std::cout << "Значение: " << data.c << std::endl;
    }
    else {
        std::cout << "Неверный тип" << std::endl;
    }
    
    return 0;
}