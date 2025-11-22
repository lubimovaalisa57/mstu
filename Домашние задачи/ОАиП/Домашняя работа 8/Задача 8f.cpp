#include <iostream>
#include <fstream>
#include <string>

int main() 
{
    std::ifstream file1("file1.txt");
    std::ifstream file2("file2.txt");
    
    if (!file1.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл file1.txt" << std::endl;
        return 1;
    }
    if (!file2.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл file2.txt " << std::endl;
        file1.close();
        return 1;
    }
    
    std::string line1, line2;
    int lineNumber = 1;
    bool filesAreIdentical = true;
    
    // Сравниваем файлы построчно
    while (std::getline(file1, line1) && std::getline(file2, line2)) {
        if (line1 != line2) {
            std::cout << "Файлы различаются в строке " << lineNumber << ":" << std::endl;
            std::cout << " file1.txt" << ": " << line1 << std::endl;
            std::cout << "file2.txt"<< ": " << line2 << std::endl;
            filesAreIdentical = false;
            break;
        }
        lineNumber++;
    }
    
    // Проверяем, не закончился ли один из файлов раньше
    if (filesAreIdentical) {
        if (std::getline(file1, line1)) {
            std::cout << "Файлы различаются: file1.txt имеет больше строк" << std::endl;
            filesAreIdentical = false;
        } else if (std::getline(file2, line2)) {
            std::cout << "Файлы различаются: file2.txt имеет больше строк" << std::endl;
            filesAreIdentical = false;
        }
    }
    
    file1.close();
    file2.close();
    
    if (filesAreIdentical == true) {
        std::cout << "Файлы идентичны." << std::endl;
    } 
    else {
        std::cout << "Файлы различаются." << std::endl;
    }
    
    return 0;
}