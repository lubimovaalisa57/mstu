#include <iostream>

int main() 
{
    char text[100];
    std::cout << "Введите текст: ";
    std::cin.getline(text, 100);
    
    int length = std::strlen(text);
    bool new_sentence = true;
    
    for (int i = 0; i < length; ++i) {
        if (new_sentence == true && std::isalpha(text[i])) {
            text[i] = std::toupper(text[i]);
            new_sentence = false;
        }
        
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            new_sentence = true;
        }
    }
    
    std::cout << "Результат: " << text << std::endl;
    
    return 0;
}