#include <iostream>

int main() 
{
    char str[100];
    std::cout << "Введите строку: ";
    std::cin.getline(str, 100);
    
    int glasn = 0;
    int soglasn = 0;
    int length = std::strlen(str);
    
    for (int i = 0; i < length; ++i) {
        char c = std::toupper(str[i]);
        
        if (c >= 'A' && c <= 'Z') {
            if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y') {
                glasn++;
            } 
            else {
                soglasn++;
            }
        }
    }
    
    std::cout << "Гласных: " << glasn << std::endl;
    std::cout << "Согласных: " << soglasn << std::endl;
    
    return 0;
}