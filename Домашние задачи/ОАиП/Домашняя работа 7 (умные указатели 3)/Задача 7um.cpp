#include <iostream>
#include <memory>
#include <cstring>

bool isVowel(char c) 
{
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

int main()
 {
    const char* str = "Hello World";
    int len = strlen(str);
    std::unique_ptr<char[]> arr = std::make_unique<char[]>(len + 1);
    strcpy(arr.get(), str);  // Копирование строки
    
    int vowels = 0, consonants = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(arr[i])) {
            if (isVowel(arr[i])) vowels++;
            else consonants++;
        }
    }
    
    // Массив гласных
    std::unique_ptr<char[]> vowelsArr = std::make_unique<char[]>(vowels + 1);
    for (int i = 0, j = 0; i < len; i++) {
        if (isalpha(arr[i]) && isVowel(arr[i])) {
            vowelsArr[j++] = arr[i];
        }
    }
    vowelsArr[vowels] = '\0';
    
    std::cout << "Гласные: " << vowels << " Согласные: " << consonants << std::endl;
    std::cout << "Гласные буквы: " << vowelsArr.get() << std::endl;
    return 0;
}