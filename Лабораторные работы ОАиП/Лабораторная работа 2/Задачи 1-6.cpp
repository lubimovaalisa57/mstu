#include <iostream>
#include <cstring>

int main() 
{
    char str[1000];
    std::cout << "Введите строку: ";
    std::cin.getline(str, 1000);
    
    // 1. Количество слов, оканчивающихся на букву a
    int count_A = 0;
    char* word = strtok(str, " ");
    
    while (word != NULL) {
        int len = strlen(word);
        if (word[len - 1] == 'a' || word[len - 1] == 'A') {
            count_A++;
        }
        word = strtok(NULL, " ");
    }
    
    std::cout << "Количество слов на 'a': " << count_A << std::endl;
    
    // 2. Длина самого короткого слова
    char str2[1000];
    std::cout << "Введите строку: ";
    std::cin.getline(str2, 1000);
    
    int minLength = 1000;
    char* word2 = strtok(str2, " ");
    
    while (word2 != NULL) {
        int len = strlen(word2);
        if (len < minLength) {
            minLength = len;
        }
        word2 = strtok(NULL, " ");
    }
    
    std::cout << "Длина самого короткого слова: " << minLength << std::endl;
    
    // 3. Количество букв b во втором слове
    char str3[1000];
    std::cout << "Введите строку: ";
    std::cin.getline(str3, 1000);
    
    int countB = 0;
    char* word3 = strtok(str3, " ");
    int wordCount = 0;
    
    while (word3 != NULL) {
        wordCount++;
        if (wordCount == 2) {
            for (int i = 0; i < strlen(word3); i++) {
                if (word3[i] == 'b' || word3[i] == 'B') {
                    countB++;
                }
            }
            break;
        }
        word3 = strtok(NULL, " ");
    }
    
    std::cout << "Количество 'b' во втором слове: " << countB << std::endl;
    
    // 4. Замена заглавных букв на строчные
    char str4[1000];
    std::cout << "Введите строку: ";
    std::cin.getline(str4, 1000);
    
    for (int i = 0; i < strlen(str4); i++) {
        if (str4[i] >= 'A' && str4[i] <= 'Z') {
            str4[i] = str4[i] + 32;
        }
    }
    
    std::cout << "Строка в нижнем регистре: " << str4 << std::endl;
    
    // 5. Количество слов с одинаковыми первым и последним символами
    char str5[1000];
    std::cout << "Введите строку: ";
    std::cin.getline(str5, 1000);
    
    int countSame = 0;
    char* word5 = strtok(str5, " ");
    
    while (word5 != NULL) {
        int len = strlen(word5);
        if (word5[0] == word5[len - 1]) {
            countSame++;
        }
        word5 = strtok(NULL, " ");
    }
    
    std::cout << "Слов с одинаковыми первым и последним символом: " << countSame << std::endl;
    
    return 0;
}