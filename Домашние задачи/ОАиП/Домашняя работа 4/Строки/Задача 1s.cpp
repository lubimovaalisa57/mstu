#include <iostream>

int main() {
    char str[100];
    std::cout << "Введите строку: ";
    std::cin.getline(str, 100); 
    
    int left = 0;
    int right = std::strlen(str) - 1;
    bool isPalindrome = true; 
    
    // Основной цикл проверки - идем с двух концов к центру
    while (left < right) {
        // Пропускаем пробелы слева
        while (std::isspace(str[left]) && left < right) {
            left++;
        }
        // Пропускаем пробелы справа
        while (std::isspace(str[right]) && left < right) {
            right--;
        }
        
        // Сравниваем символы
        if (std::tolower(str[left]) != std::tolower(str[right])) {
            isPalindrome = false; 
            break;
        }
        left++;
        right--;
    }
    
    if (isPalindrome == true) {
        std::cout << "Палиндром" << std::endl;
    } 
    else {
        std::cout << "Не палиндром" << std::endl;
    }
    
    return 0;
}