#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

int main() 
{
    std::ifstream inputFile("vibration_log.txt");
    
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл vibration_log.txt" << std::endl;
        return 1;
    }
    
    std::vector<double> amplitudes;
    double value;
    
    while (inputFile >> value) {
        amplitudes.push_back(value);
    }
    
    inputFile.close();
    
    // Лямбда-функции для анализа
    auto filterAbove005 = [](double x) { return x > 0.05; };
    
    auto calculateAverage = [](const std::vector<double>& vec) {
        return std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
    };
    
    auto findMin = [](const std::vector<double>& vec) {
        return *std::min_element(vec.begin(), vec.end());
    };
    
    auto findMax = [](const std::vector<double>& vec) {
        return *std::max_element(vec.begin(), vec.end());
    };
    
    // Применяем фильтрацию
    std::vector<double> filteredAmplitudes;
    std::copy_if(amplitudes.begin(), amplitudes.end(), 
                 std::back_inserter(filteredAmplitudes), filterAbove005);
    
    // Вычисляем статистику
    double average = calculateAverage(amplitudes);
    double minVal = findMin(amplitudes);
    double maxVal = findMax(amplitudes);
    
    std::ofstream reportFile("vibration_report.txt");
    
    if (!reportFile.is_open()) {
        std::cerr << "Ошибка: Не удалось создать файл vibration_report.txt" << std::endl;
        return 1;
    }
    
    reportFile << std::fixed << std::setprecision(4);
    reportFile << "Количество измерений: " << amplitudes.size() << std::endl;
    reportFile << "Фильтрованные значения (>0.05): ";
    for (double val : filteredAmplitudes) {
        reportFile << val << " ";
    }
    reportFile << std::endl;
    reportFile << "Среднее значение: " << average << std::endl;
    reportFile << "Минимум: " << minVal << std::endl;
    reportFile << "Максимум: " << maxVal << std::endl;
    
    reportFile.close();
    
    std::cout << "Анализ вибрационных данных завершён. Отчёт сохранён в vibration_report.txt" << std::endl;
    
    return 0;
}