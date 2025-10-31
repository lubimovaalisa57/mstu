#include <iostream>

void replaceSpaces(char* str) 
{
    char* ptr = str;
    
    while (*ptr != '\0') {
        if (*ptr == ' ') {
            *ptr = '_';
        }
        ptr++;
    }
}

int main() 
{
    const int MAX_SIZE = 100;
    char inputString[MAX_SIZE];
    
    std::cout << "Введите строку: ";
    std::cin.getline(inputString, MAX_SIZE);
    
    replaceSpaces(inputString);

    std::cout << "Результат: " << inputString << std::endl;
    
    return 0;
}