#include <iostream>
#include <cstring>

int main() 
{
    char str[1000];
    std::cout << "Введите строку: ";
    std::cin.getline(str, 1000);
    
    char* words[100];
    int word_count = 0;
    char* token = strtok(str, " ");
    while (token != NULL && word_count < 100) {
        words[word_count++] = token;
        token = strtok(NULL, " ");
    }
    
    char shortest_common[100] = "";
    
    // Сравниваем все пары слов
    for (int i = 0; i < word_count; ++i) {
        for (int j = i + 1; j < word_count; ++j) {
            char* word1 = words[i];
            char* word2 = words[j];
            
            int len1 = strlen(word1);
            int len2 = strlen(word2);
            
            // Ищем общие подстроки
            for (int start1 = 0; start1 < len1; ++start1) {
                for (int start2 = 0; start2 < len2; ++start2) {
                    int common_len = 0;
                    while (start1 + common_len < len1 && 
                           start2 + common_len < len2 && 
                           word1[start1 + common_len] == word2[start2 + common_len]) {
                        common_len++;
                    }
                    
                    if (common_len >= 2) {
                        char common_sub[100];
                        strncpy(common_sub, &word1[start1], common_len);
                        common_sub[common_len] = '\0';
                        
                        if (strlen(shortest_common) == 0 || common_len < strlen(shortest_common)) {
                            strcpy(shortest_common, common_sub);
                        }
                    }
                }
            }
        }
    }
    
    if (strlen(shortest_common) > 0) {
        std::cout << "Самая короткая общая подстрока: " << shortest_common << std::endl;
    } else {
        std::cout << "Общих подстрок не найдено" << std::endl;
    }
    
    return 0;
}