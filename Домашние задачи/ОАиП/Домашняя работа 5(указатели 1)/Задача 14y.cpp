#include <iostream>
#include <vector>

double computeRMS(const std::vector<double>& signal) 
{
    // Получаем указатель на начало данных вектора
    const double* p = signal.data();
    
    double sum = 0.0;
    int N = signal.size();
    
    // Вычисляем сумму квадратов через арифметику указателей
    for (int i = 0; i < N; i++) {
        double value = *(p + i); 
        sum += value * value;    
    }
    
    // Вычисляем RMS
    return std::sqrt(sum / N);
}

int main() 
{
    std::vector<double> signal = {2.0, 3.0, 1.0, 4.0, 3.0};
    
    double rms = computeRMS(signal);
    
    std::cout << "RMS value: " << rms << std::endl;
    
    return 0;
}