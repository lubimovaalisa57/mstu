#include <iostream>

int main() 
{
    char str[100];
    char symbol;
    std::cout << "Введите строку: ";
    std::cin.getline(str, 100);
    std::cout << "Введите символ для удаления: ";
    std::cin >> symbol;
    
    int length = std::strlen(str);
    int write_index = 0;
    
    for (int read_index = 0; read_index < length; ++read_index) {
        if (str[read_index] != symbol) {
            str[write_index] = str[read_index];
            write_index++;
        }
    }
    
    str[write_index] = '\0';
    
    std::cout << "Результат: " << str << std::endl;
    
    return 0;
}