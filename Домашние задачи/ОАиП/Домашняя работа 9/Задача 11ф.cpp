#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() 
{
    std::ifstream in("sensor_data.txt");
    std::vector<double> temperatures;
    double temp;
    
    while (in >> temp) {
        temperatures.push_back(temp);
    }
    in.close();
    
    // Фильтрация некорректных значений
    auto valid_temp = [](double t) { return t >= -50 && t <= 50; };
    temperatures.erase(std::remove_if(temperatures.begin(), temperatures.end(), 
                                     [](double t) { return t < -50 || t > 50; }), 
                      temperatures.end());
    
    // Сохранение отфильтрованных данных
    std::ofstream out("filtered_sensor_data.txt");
    for (double t : temperatures) {
        out << t << std::endl;
    }
    out.close();
    
    // Вычисление средней температуры
    double sum = std::accumulate(temperatures.begin(), temperatures.end(), 0.0);
    double average = sum / temperatures.size();
    
    std::cout << "Средняя температура: " << average << std::endl;
    std::cout << "Отфильтровано значений: " << temperatures.size() << std::endl;
    
    return 0;
}