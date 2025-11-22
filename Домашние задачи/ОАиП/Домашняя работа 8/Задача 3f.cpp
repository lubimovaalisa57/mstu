#include <iostream>
#include <fstream>
#include <string>

int main() 
{
    std::ifstream inputFile("text.txt");
    
    // Проверяем, успешно ли открыт файл
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл "<< std::endl;
        return 1;
    }
    
    int wordCount = 0;
    std::string word;
    
    // Читаем слова из файла с помощью оператора >>
    while (inputFile >> word) {
        wordCount++;
    }
    
    // Закрываем файл
    inputFile.close();
    
    // Выводим результат
    std::cout << "Количество слов в файле: " << wordCount << std::endl;
    
    return 0;
}