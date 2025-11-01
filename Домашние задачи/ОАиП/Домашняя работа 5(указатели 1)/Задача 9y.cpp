#include <iostream>

void removeSpaces(char* str) 
{
    char* read_ptr = str;  // указатель для чтения
    char* write_ptr = str; // указатель для записи
    
    // Проходим по строке одним проходом
    while (*read_ptr != '\0') {
        if (*read_ptr != ' ') {
            // Если не пробел, копируем символ
            *write_ptr = *read_ptr;
            write_ptr++;
        }
        read_ptr++;
    }
    
    *write_ptr = '\0';
}

int main() 
{
    const int MAX_SIZE = 100;
    char input[MAX_SIZE];

    std::cout << "Введите строку: ";
    std::cin.getline(input, MAX_SIZE);
    
    removeSpaces(input);
    
    std::cout << "Без пробелов: " << input << std::endl;
    
    return 0;
}