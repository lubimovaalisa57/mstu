#include <iostream>

void myStrCat(char* dest, const char* src) 
{
    while (*dest != '\0') {
        dest++;
    }
    
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    
    *dest = '\0';
}

int main() 
{
    const int MAX_SIZE = 100;
    char str1[MAX_SIZE];
    char str2[MAX_SIZE];
    char result[MAX_SIZE * 2];
    
    std::cout << "Введите первую строку: ";
    std::cin.getline(str1, MAX_SIZE);
    
    std::cout << "Введите вторую строку: ";
    std::cin.getline(str2, MAX_SIZE);
    
    char* ptr = result;
    const char* src_ptr = str1;
    while (*src_ptr != '\0') {
        *ptr = *src_ptr;
        ptr++;
        src_ptr++;
    }
    *ptr = '\0';
    
    // Конкатенируем вторую строку
    myStrCat(result, str2);
    
    std::cout << "Результат: " << result << std::endl;
    
    return 0;
}