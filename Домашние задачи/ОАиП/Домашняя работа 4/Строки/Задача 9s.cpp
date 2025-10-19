#include <iostream>
#include <cstring>

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
    
    // Создаем двумерный массив dp
    int** dp = new int*[len1 + 1];
    for (int i = 0; i <= len1; ++i) {
        dp[i] = new int[len2 + 1];
        for (int j = 0; j <= len2; ++j) {
            dp[i][j] = 0;
        }
    }
    
    int max_length = 0;
    int end_index_str1 = 0;
    
    // Заполняем массив dp
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > max_length) {
                    max_length = dp[i][j];
                    end_index_str1 = i - 1;
                }
            } 
            else {
                dp[i][j] = 0;
            }
        }
    }
    
    // Выводим результат
    if (max_length > 0) {
        std::cout << "Наибольшая общая подстрока: ";
        for (int i = end_index_str1 - max_length + 1; i <= end_index_str1; ++i) {
            std::cout << str1[i];
        }
        std::cout << std::endl;
        std::cout << "Длина: " << max_length << std::endl;
    } 
    else {
        std::cout << "Общих подстрок не найдено" << std::endl;
    }
    
    return 0;
}