#include <iostream>

int main() 
{
    char str[100];
    char old_sub[50];
    char new_sub[50];
    char result[200];
    std::cout << "Введите строку: ";
    std::cin.getline(str, 100);
    std::cout << "Введите подстроку для замены: ";
    std::cin.getline(old_sub, 50);
    
    std::cout << "Введите новую подстроку: ";
    std::cin.getline(new_sub, 50);
    
    int str_len = std::strlen(str);
    int old_len = std::strlen(old_sub);
    int new_len = std::strlen(new_sub);
    
    int result_index = 0;
    
    for (int i = 0; i < str_len; ) {
        bool found = true;
        
        // Проверяем, совпадает ли подстрока
        for (int j = 0; j < old_len; ++j) {
            if (i + j >= str_len || str[i + j] != old_sub[j]) {
                found = false;
                break;
            }
        }
        
        if (found == true) {
            // Копируем новую подстроку
            for (int j = 0; j < new_len; ++j) {
                result[result_index] = new_sub[j];
                result_index++;
            }
            i += old_len;
        } else {
            // Копируем текущий символ
            result[result_index] = str[i];
            result_index++;
            i++;
        }
    }
    
    result[result_index] = '\0';
    
    std::cout << "Результат: " << result << std::endl;
    
    return 0;
}