#include <iostream>
//#include <algorithm>

int main() 
{
    char str[100];
    std::cout << "Введите строку: ";
    std::cin.getline(str, 100);
    
    int length = std::strlen(str);
    int start = 0;
    
    for (int i = 0; i <= length; ++i) {
        if (str[i] == ' ' || str[i] == '\0') {
            // Переворачиваем слово от start до i-1
            int left = start;
            int right = i - 1;
            
            while (left < right) {
                std::swap(str[left], str[right]);
                left++;
                right--;
            }
            
            start = i + 1;
        }
    }
    
    std::cout << "Результат: " << str << std::endl;
    
    return 0;
}