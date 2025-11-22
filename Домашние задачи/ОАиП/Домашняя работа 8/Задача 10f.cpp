#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <numeric>
#include <iomanip>

int main() 
{
    std::ifstream inputFile("power_log.txt");
    
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл power_log.txt" << std::endl;
        return 1;
    }
    
    std::map<std::string, std::vector<double>> deviceData;
    std::string line;
    
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string timestamp, deviceName;
        double power;
        
        if (iss >> timestamp >> deviceName >> power) {
            deviceData[deviceName].push_back(power);
        }
    }
    
    inputFile.close();
    
    std::ofstream reportFile("energy_report.txt");
    
    if (!reportFile.is_open()) {
        std::cerr << "Ошибка: Не удалось создать файл energy_report.txt" << std::endl;
        return 1;
    }
    
    for (const auto& data : deviceData) {
        std::string deviceName = data.first;
        std::vector<double> powerReadings = data.second;
        
        if (powerReadings.empty()) {
            continue;
        }
        
        int measurements = powerReadings.size();
        double total = std::accumulate(powerReadings.begin(), powerReadings.end(), 0.0);
        double average = total / measurements;
        
        reportFile << std::fixed << std::setprecision(2);
        reportFile << deviceName << ": measurements = " << measurements 
                  << ", total = " << total << " kWh"
                  << ", average = " << average << " kW" 
                  << std::endl;
    }
    
    reportFile.close();
    
    std::cout << "Анализ завершён. Результаты сохранены в energy_report.txt" << std::endl;
    
    return 0;
}