#include <iostream>

const char* findSubstring(const char* text, const char* word) 
{
    // Если подстрока пустая, возвращаем начало текста
    if (*word == '\0') {
        return text;
    }
    
    const char* text_ptr = text;
    
    while (*text_ptr != '\0') {
        const char* t = text_ptr;
        const char* w = word;
        
        // Сравниваем подстроку с текущей позицией в тексте
        while (*t != '\0' && *w != '\0' && *t == *w) {
            t++;
            w++;
        }
        
        // Если дошли до конца подстроки - нашли вхождение
        if (*w == '\0') {
            return text_ptr;
        }
        
        text_ptr++;
    }
    
    return nullptr;
}

int main() 
{
    const int MAX_SIZE = 100;
    char text[MAX_SIZE];
    char word[MAX_SIZE];
    
    std::cout << "Введите текст: ";
    std::cin.getline(text, MAX_SIZE);
    
    std::cout << "Введите подстроку для поиска: ";
    std::cin.getline(word, MAX_SIZE);
    
    const char* result = findSubstring(text, word);

    if (result != nullptr) {
        std::cout << "Подстрока найдена по индексу: " << (result - text) << std::endl;
        std::cout << "Фрагмент текста: " << result << std::endl;
    } 
    else {
        std::cout << "Подстрока не найдена" << std::endl;
    }
    
    return 0;
}