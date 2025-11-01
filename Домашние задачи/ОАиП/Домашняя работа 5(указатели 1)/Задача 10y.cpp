#include <iostream>

int myStrCmp(const char* s1, const char* s2) 
{
    const char* p1 = s1;
    const char* p2 = s2;
    
    while (*p1 != '\0' && *p2 != '\0' && *p1 == *p2) {
        p1++;
        p2++;
    }
    
    return *p1 - *p2;
}

int main() 
{
    const int MAX_SIZE = 100;
    char str1[MAX_SIZE];
    char str2[MAX_SIZE];
    
    std::cout << "Введите первую строку: ";
    std::cin.getline(str1, MAX_SIZE);

    std::cout << "Введите вторую строку: ";
    std::cin.getline(str2, MAX_SIZE);
    
    int result = myStrCmp(str1, str2);
    
    std::cout << "Результат сравнения:" << std::endl;
    std::cout << "Строка 1: " << str1 << std::endl;
    std::cout << "Строка 2: " << str2 << std::endl;
    
    if (result == 0) {
        std::cout << "Строки равны" << std::endl;
    } 
    else if (result < 0) {
        std::cout << "Первая строка меньше второй" << std::endl;
    } 
    else {
        std::cout << "Первая строка больше второй" << std::endl;
    }
    
    std::cout << "Числовое значение: " << result << std::endl;
    
    return 0;
}