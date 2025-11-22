#include <iostream>
#include <fstream>
#include <string>

int main() 
{
    // Создаем объект для чтения файла
    std::ifstream inputFile("input.txt");
    
    // Проверяем, успешно ли открыт файл
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл input.txt" << std::endl;
        return 1; 
    }
    
    std::cout << "Содержимое файла:" << std::endl;
    
    std::string line;
    int lineNumber = 1;
    
    // Читаем файл построчно до конца
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
        lineNumber++;
    }
    
    // Закрываем файл (автоматически закроется при выходе из области видимости)
    inputFile.close();
    
    std::cout << "Файл прочитан успешно" << std::endl;
    
    return 0;
}