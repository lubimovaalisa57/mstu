#include <iostream>
#include <fstream>
#include <string>

int main() 
{
    std::ifstream sourceFile("source.txt");
    
    if (!sourceFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл source.txt"<< std::endl;
        return 1;
    }
    
    std::ofstream copyFile("copy.txt");
    
    // Проверяем, успешно ли открыт целевой файл
    if (!copyFile.is_open()) {
        std::cerr << "Ошибка: Не удалось создать файл copy.txt" << std::endl;
        sourceFile.close();
        return 1;
    }
    
    int lineCount = 0;
    std::string line;
    
    // Копируем файл построчно
    while (std::getline(sourceFile, line)) {
        copyFile << line << std::endl;
        lineCount++;
    }
    
    sourceFile.close();
    copyFile.close();
    
    std::cout << "Файл успешно скопирован." << std::endl;
    std::cout << "Количество скопированных строк: " << lineCount << std::endl;
    
    return 0;
}