#include <iostream>

int main() 
{
    char str[100];
    std::cout << "Введите строку: ";
    std::cin.getline(str, 100);
    
    char result[100];
    int write_index = 0;
    int length = std::strlen(str);
    
    for (int read_index = 0; read_index < length; ++read_index) {
        if (str[read_index] < '0' || str[read_index] > '9') {
            result[write_index] = str[read_index];
            write_index++;
        }
    }
    
    result[write_index] = '\0';
    
    std::cout << "Результат: " << result << std::endl;
    
    return 0;
}