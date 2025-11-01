#include <iostream>

bool isPalindrome(const char* str) 
{
    const char* left = str;
    const char* right = str;
    
    while (*right != '\0') {
        right++;
    }
    right--; // Указываем на последний символ
    
    while (left < right) {
        if (*left != *right) {
            return false;
        }
        left++;
        right--;
    }
    
    return true;
}

int main()
{
    char str[100];
    
    std::cout << "Введите строку: ";
    std::cin.getline(str, 100);
    
    if (isPalindrome(str) == true) {
        std::cout << "Строка " << str <<" является палиндромом" << std::endl;
    } 
    else {
        std::cout << "Строка " << str << " не является палиндромом" << std::endl;
    }
    
    return 0;
}