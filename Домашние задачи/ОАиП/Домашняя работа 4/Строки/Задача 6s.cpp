#include <iostream>

int main() 
{
    char text[100];
    int shift;
    std::cout << "Текст: ";
    std::cin.getline(text, 100);
    std::cout << "Сдвиг: ";
    std::cin >> shift;
    
    int length = std::strlen(text);
    
    for (int i = 0; i < length; ++i) {
        if (std::isupper(text[i])) {
            text[i] = (text[i] - 'A' + shift) % 26 + 'A';
        } else if (std::islower(text[i])) {
            text[i] = (text[i] - 'a' + shift) % 26 + 'a';
        }
    }
    
    std::cout << "Результат: " << text << std::endl;
    
    return 0;
}