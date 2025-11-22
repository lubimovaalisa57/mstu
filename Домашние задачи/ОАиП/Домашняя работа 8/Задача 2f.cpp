#include <iostream>
#include <fstream>
#include <string>

int main() 
{
    // Создаем объект для чтения файла
    std::ifstream inputFile("data.txt");
    
    // Проверяем, успешно ли открыт файл
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл data.txt" << std::endl;
        return 1;
    }
    
    int lineCount = 0;
    std::string line;
    
    // Читаем файл построчно и подсчитываем строки
    while (std::getline(inputFile, line)) {
        lineCount++;
    }
    
    inputFile.close();
    
    std::cout << "Количество строк в файле: " << lineCount << std::endl;
    
    return 0;
}