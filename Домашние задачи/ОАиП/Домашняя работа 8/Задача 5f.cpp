#include <iostream>
#include <fstream>

int main() 
{
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл input.txt " << std::endl;
        return 1;
    }
    
    int charCount = 0;
    char ch;
    
    // Читаем файл посимвольно с помощью .get(ch)
    while (inputFile.get(ch)) {
        charCount++;
    }
    
    inputFile.close();

    std::cout << "Количество символов в файле: " << charCount << std::endl;
    
    return 0;
}