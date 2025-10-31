#include <iostream>

int countCharacter(const char* str, char target) 
{
    int count = 0;
    const char* ptr = str;
    
    while (*ptr != '\0') {
        if (*ptr == target) {
            count++;
        }
        ptr++;
    }
    return count;
}

int main() 
{
    const int MAX_SIZE = 100;
    char inputString[MAX_SIZE];
    char searchChar;

    std::cout << "Введите строку: ";
    std::cin.getline(inputString, MAX_SIZE);
    
    std::cout << "Введите символ для поиска: ";
    std::cin >> searchChar;
    
    int result = countCharacter(inputString, searchChar);
    
    std::cout << "Количество вхождений: " << result << std::endl;
    
    return 0;
}