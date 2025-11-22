#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

int main() 
{
    std::ifstream inputFile("temperature_data.txt");
    
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл temperature_data.txt" << std::endl;
        return 1;
    }
    
    std::map<std::string, std::vector<double>> sensorData;
    std::string line;
    
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string sensorName;
        double temperature;
        
        if (iss >> sensorName >> temperature) {
            sensorData[sensorName].push_back(temperature);
        }
    }
    
    inputFile.close();
    
    std::ofstream reportFile("report.txt");
    
    if (!reportFile.is_open()) {
        std::cerr << "Ошибка: Не удалось создать файл report.txt" << std::endl;
        return 1;
    }
    
    for (const auto& data : sensorData) {
        std::string sensorName = data.first;
        std::vector<double> temperatures = data.second;
        
        if (temperatures.empty()) {
            continue;
        }
        
        double minTemp = *std::min_element(temperatures.begin(), temperatures.end());
        double maxTemp = *std::max_element(temperatures.begin(), temperatures.end());
        double sum = std::accumulate(temperatures.begin(), temperatures.end(), 0.0);
        double avgTemp = sum / temperatures.size();
        
        reportFile << std::fixed << std::setprecision(1);
        reportFile << sensorName << ": min = " << minTemp 
                  << ", max = " << maxTemp 
                  << ", avg = " << avgTemp 
                  << std::endl;
    }
    
    reportFile.close();
    
    std::cout << "Отчёт о температурных данных сохранён в report.txt" << std::endl;
    
    return 0;
}