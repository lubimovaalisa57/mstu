#include <iostream>

int main() 
{
    char str1[100];
    char str2[100];
    std::cout << "Введите первую строку: ";
    std::cin.getline(str1, 100);
    std::cout << "Введите вторую строку: ";
    std::cin.getline(str2, 100);
    
    int len1 = std::strlen(str1);
    int len2 = std::strlen(str2);
    
    // Если длины разные - не могут быть анаграммами
    if (len1 != len2) {
        std::cout << "Нет" << std::endl;
        return 0;
    }
    
    // Сортируем обе строки
    for (int i = 0; i < len1 - 1; ++i) {
        for (int j = i + 1; j < len1; ++j) {
            if (str1[i] > str1[j]) {
                std::swap(str1[i], str1[j]);
            }
        }
    }
    
    for (int i = 0; i < len2 - 1; ++i) {
        for (int j = i + 1; j < len2; ++j) {
            if (str2[i] > str2[j]) {
                std::swap(str2[i], str2[j]);
            }
        }
    }
    
    // Сравниваем отсортированные строки
    bool is_anagram = true;
    for (int i = 0; i < len1; ++i) {
        if (str1[i] != str2[i]) {
            is_anagram = false;
            break;
        }
    }
    
    if (is_anagram == true) {
        std::cout << "Да" << std::endl;
    } 
    else {
        std::cout << "Нет" << std::endl;
    }
    
    return 0;
}