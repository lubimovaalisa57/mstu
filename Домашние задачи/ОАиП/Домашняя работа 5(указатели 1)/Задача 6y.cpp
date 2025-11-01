#include <iostream>

void reverse(char* str) 
{
    char* start = str;
    char* end = str;
    
    // Находим конец строки
    while (*end != '\0') {
        end++;
    }
    end--; // Указываем на последний символ
    
    // Меняем символы местами
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        
        start++;
        end--;
    }
}

int main() 
{
    char str[100];
    
    std::cout << "Введите строку: ";
    std::cin.getline(str, 100);
    
    reverse(str);
    
    std::cout << "Перевернутая строка: " << str << std::endl;
    
    return 0;
}