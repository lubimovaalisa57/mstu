#include <iostream>

int main() 
{
    char str[100];
    std::cout << "Введите строку: ";
    std::cin.getline(str, 100);
    
    char unique[100];
    int count = 0;
    int length = std::strlen(str);
    
    for (int i = 0; i < length; ++i) {
        bool found = false;
        
        for (int j = 0; j < i; ++j) {
            if (str[i] == str[j]) {
                found = true;
                break;
            }
        }
        
        if (found == false) {
            unique[count] = str[i];
            count++;
        }
    }
    
    std::cout << "Уникальные символы: ";
    for (int i = 0; i < count; ++i) {
        std::cout << unique[i];
        if (i < count - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    
    return 0;
}