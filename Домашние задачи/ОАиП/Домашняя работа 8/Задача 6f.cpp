#include <iostream>
#include <fstream>
#include <string>

int main() 
{
    std::ofstream outputFile("output.txt");
    
    if (!outputFile.is_open()) {
        std::cerr << "Ошибка: Не удалось создать файл output.txt" << std::endl;
        return 1;
    }
    
    std::string line;
    int lineCount = 0;
    
    std::cout << "Введите строки (пустая строка завершает ввод):" << std::endl;
    
    // Читаем первую строку
    std::getline(std::cin, line);
    
    // Продолжаем читать, пока строка не пустая
    while (!line.empty()) {
        // Записываем строку в файл
        outputFile << line << std::endl;
        lineCount++;
        
        // Читаем следующую строку
        std::getline(std::cin, line);
    }
    
    outputFile.close();
    
    std::cout << "Количество записанных строк: " << lineCount << std::endl;
    
    return 0;
}