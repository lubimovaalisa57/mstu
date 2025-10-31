#include <iostream>

int myStrLen(const char* str) 
{
    const char* ptr = str;
    
    while (*ptr != '\0') {
        ptr++;
    }
    
    return ptr - str;
}

int main() 
{
    const int MAX_SIZE = 100;
    char userString[MAX_SIZE];
    
    std::cout << "Введите строку: ";
    std::cin.getline(userString, MAX_SIZE);
    
    std::cout << "Длина строки: " << myStrLen(userString) << std::endl;
    
    return 0;
}