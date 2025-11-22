#include <iostream>
#include <fstream>

int main() 
{
    std::ifstream inputFile("numbers.txt");
    
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл numbers.txt " << std::endl;
        return 1;
    }
    
    int number;
    int count = 0;
    int sum = 0;
    
    // Читаем числа из файла с помощью оператора >>
    while (inputFile >> number) {
        count++;
        sum += number;
    }

    inputFile.close();
    
    // Вычисляем среднее значение
    double average = 0.0;
    if (count > 0) {
        average = static_cast<double>(sum) / count;
    }
    
    std::cout << "Количество чисел: " << count << std::endl;
    std::cout << "Сумма: " << sum << std::endl;
    std::cout << "Среднее: " << average << std::endl;
    
    return 0;
}