#include <iostream>

int main() 
{
    char str[100];
    int k;
    std::cout << "Введите строку: ";
    std::cin.getline(str, 100);
    std::cout << "Введите k: ";
    std::cin >> k;
    
    int length = std::strlen(str);
    
    std::cout << "Подстроки длины " << k << " с уникальными символами:" << std::endl;
    
    for (int i = 0; i <= length - k; ++i) {
        bool has_duplicate = false;
        
        // Проверяем уникальность символов в текущей подстроке
        for (int j = i; j < i + k; ++j) {
            for (int m = j + 1; m < i + k; ++m) {
                if (str[j] == str[m]) {
                    has_duplicate = true;
                    break;
                }
            }
            if (has_duplicate == true) {
                break;
            }
        }
        
        if (has_duplicate == true) {
            continue;
        }
        
        // Проверяем, не выводили ли мы уже такую подстроку
        bool already_printed = false;
        for (int prev = 0; prev < i; ++prev) {
            bool is_same = true;
            for (int j = 0; j < k; ++j) {
                if (str[prev + j] != str[i + j]) {
                    is_same = false;
                    break;
                }
            }
            if (is_same == true) {
                already_printed = true;
                break;
            }
        }
        
        if (already_printed == false) {
            for (int j = i; j < i + k; ++j) {
                std::cout << str[j];
            }
            std::cout << std::endl;
        }
    }
    
    return 0;
}