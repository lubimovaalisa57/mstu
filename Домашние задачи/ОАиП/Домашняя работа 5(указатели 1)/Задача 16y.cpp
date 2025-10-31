#include <iostream>
#include <vector>

void analyzePressure(const std::vector<double>& data, double& minVal, double& maxVal, double& avgVal) 
{
    // Проверка на пустой вектор
    if (data.empty()) {
        minVal = maxVal = avgVal = 0.0;
        return;
    }
    
    // Получаем указатель на первый элемент вектора
    const double* p = data.data();
    // Вычисляем указатель на позицию после последнего элемента
    const double* end = p + data.size();
    
    // Инициализируем значения первым элементом
    minVal = maxVal = avgVal = *p;
    double sum = *p; 
    
    while (++p < end) {
        if (*p < minVal) minVal = *p;
        if (*p > maxVal) maxVal = *p;
        sum += *p;
    }
    avgVal = sum / data.size();
}

int main() 
{
    std::vector<double> pressure = {101.3, 100.8, 101.9, 100.5, 102.0};
    double minVal, maxVal, avgVal;  

    analyzePressure(pressure, minVal, maxVal, avgVal);
    
    std::cout << "Min pressure: " << minVal << std::endl;
    std::cout << "Max pressure: " << maxVal << std::endl;
    std::cout << "Average pressure: " << avgVal << std::endl;
    
    return 0;
}