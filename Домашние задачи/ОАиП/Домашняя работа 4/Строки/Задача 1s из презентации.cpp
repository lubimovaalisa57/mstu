#include <iostream>

int main() 
{
    char str[100];
    std::cout << "Введите строку: ";
    std::cin.getline(str, 100);
    
    int max_length = 0;
    int current_length = 0;
    int max_start = 0;
    int current_start = 0;
    int length = std::strlen(str);
    
    for (int i = 0; i <= length; ++i) {
        if (str[i] == ' ' || str[i] == '\0') {
            if (current_length > max_length) {
                max_length = current_length;
                max_start = current_start;
            }
            current_start = i + 1;
            current_length = 0;
        } 
        else {
            current_length++;
        }
    }
    
    std::cout << "Самое длинное слово: ";
    for (int i = max_start; i < max_start + max_length; ++i) {
        std::cout << str[i];
    }
    std::cout << std::endl;
    
    return 0;
}