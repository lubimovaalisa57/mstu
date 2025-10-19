#include <iostream>

int main() 
{
    char str[100];
    std::cout << "Введите строку: ";
    std::cin.getline(str, 100);
    
    int length = std::strlen(str);
    int start = 0;
    
    std::cout << "Слова в строке:" << std::endl;
    
    for (int i = 0; i <= length; ++i) {
        if (str[i] == ' ' || str[i] == '\0') {
            if (start < i) {
                for (int j = start; j < i; ++j) {
                    std::cout << str[j];
                }
                std::cout << std::endl;
            }
            start = i + 1;
        }
    }
    
    return 0;
}