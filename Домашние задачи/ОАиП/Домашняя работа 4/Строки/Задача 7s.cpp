#include <iostream>

int main() 
{
    char str[100];
    std::cout << "Введите строку: ";
    std::cin.getline(str, 100);
    
    int length = std::strlen(str);
    
    std::cout << "Результат: ";
    
    int i = 0;
    while (i < length) {
        char current_char = str[i];
        int count = 1;
        
        while (i + count < length && str[i + count] == current_char) {
            count++;
        }
        
        std::cout << current_char << count;
        i += count;
    }
    
    std::cout << std::endl;
    
    return 0;
}