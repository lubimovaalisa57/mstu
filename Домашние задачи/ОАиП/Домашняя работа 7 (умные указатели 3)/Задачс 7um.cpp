#include <iostream>
#include <memory>
#include <cstring>  // для strlen
#include <cctype>   // для tolower
#include <string>   // для работы со строками

// Функция для проверки, является ли символ гласной буквой (только английские)
bool isVowel(char c) 
{
    c = std::tolower(c);  // Приводим к нижнему регистру для удобства проверки
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

// Функция для проверки, является ли символ буквой
bool isAlpha(char c) 
{
    return std::isalpha(static_cast<unsigned char>(c));
}

// Функция для проверки русских гласных (работает со строкой)
bool isRussianVowel(const std::string& str, int index) 
{
    // Для простоты проверяем только английские гласные
    // В реальном проекте для русских букв нужно использовать wchar_t или UTF-8 обработку
    return isVowel(str[index]);
}

int main() 
{
    std::string inputString = "Hello World! Programming is fun!";
    int length = inputString.length();
    
    std::cout << "Исходная строка: " << inputString << std::endl;
    std::cout << "Длина строки: " << length << std::endl;
    
    // 1. Создаем динамический массив символов с помощью unique_ptr
    std::unique_ptr<char[]> charArray = std::make_unique<char[]>(length + 1);  // +1 для нуль-терминатора
    
    // 2. Заполняем массив заданной строкой
    std::strcpy(charArray.get(), inputString.c_str());
    
    std::cout << "Содержимое массива: " << charArray.get() << std::endl;
    
    // 3. Подсчитываем количество гласных и согласных букв
    int vowelCount = 0;
    int consonantCount = 0;
    int otherCount = 0;
    
    for (int i = 0; i < length; ++i) {
        char c = charArray[i];
        if (isAlpha(c)) {
            if (isVowel(c)) {
                vowelCount++;
            }
            else {
                consonantCount++;
            }
        } 
        else {
            otherCount++;
        }
    }
    
    std::cout << "Статистика строки:" << std::endl;
    std::cout << "Гласные буквы: " << vowelCount << std::endl;
    std::cout << "Согласные буквы: " << consonantCount << std::endl;
    std::cout << "Другие символы: " << otherCount << std::endl;
    std::cout << "Всего символов: " << length << std::endl;
    
    // 4. Создаем новый массив, содержащий только гласные буквы
    if (vowelCount > 0) {
        std::unique_ptr<char[]> vowelsArray = std::make_unique<char[]>(vowelCount + 1);
        
        int vowelIndex = 0;
        for (int i = 0; i < length; ++i) {
            if (isAlpha(charArray[i]) && isVowel(charArray[i])) {
                vowelsArray[vowelIndex++] = charArray[i];
            }
        }
        vowelsArray[vowelCount] = '\0';  // Добавляем нуль-терминатор
        
        std::cout << "Массив только с гласными буквами: " << vowelsArray.get() << std::endl;
        
        // Дополнительно: выводим гласные по отдельности
        std::cout << "Гласные по отдельности: ";
        for (int i = 0; i < vowelCount; ++i) {
            std::cout << vowelsArray[i];
            if (i < vowelCount - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
        
        // vowelsArray автоматически освободится при выходе из блока
    }
    else {
        std::cout << "В строке нет гласных букв" << std::endl;
    }
    return 0;
}