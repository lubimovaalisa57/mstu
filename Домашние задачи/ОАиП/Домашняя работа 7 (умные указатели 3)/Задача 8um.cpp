#include <iostream>
#include <memory>
#include <iomanip>

double average(const std::unique_ptr<double[]>& arr, int n) 
{
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum / n;
}

int main() 
{
    const int n = 3;
    
    // Создание массивов
    std::unique_ptr<double[]> temp = std::make_unique<double[]>(n);
    std::unique_ptr<double[]> press = std::make_unique<double[]>(n);
    std::unique_ptr<double[]> hum = std::make_unique<double[]>(n);
    
    // Заполнение
    temp[0] = 22.5; temp[1] = 23.1; temp[2] = 21.8;
    press[0] = 755.2; press[1] = 756.8; press[2] = 754.5;
    hum[0] = 65.0; hum[1] = 62.5; hum[2] = 68.3;
    
    // Вывод таблицы
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Параметр\tСреднее значение" << std::endl;
    std::cout << "Температура\t" << average(temp, n) << std::endl;
    std::cout << "Давление\t" << average(press, n) << std::endl;
    std::cout << "Влажность\t" << average(hum, n) << std::endl;
    return 0;
}