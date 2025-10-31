#include <iostream>

void myStrCopy(char* dest, const char* src) {
    // Копируем символы пока не встретим нулевой терминатор
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
    char source[MAX_SIZE];
    char destination[MAX_SIZE];
    
    std::cout << "Введите строку для копирования: ";
    std::cin.getline(source, MAX_SIZE);
    
    myStrCopy(destination, source);
    
    std::cout << "Исходная: " << source  << std::endl;
    std::cout << "Копия: " << destination << std::endl;
    
    return 0;
}