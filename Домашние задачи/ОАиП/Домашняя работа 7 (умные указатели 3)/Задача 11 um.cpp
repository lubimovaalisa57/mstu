#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() 
{
    int n;
    std::cout << "Введите количество измерений: ";
    std::cin >> n;
    
    std::vector<double> signals(n);
    std::cout << "Введите " << n << " значений температур: ";
    for (int i = 0; i < n; i++) {
        std::cin >> signals[i];
    }
    
    // Создание динамического массива
    auto signals_ptr = std::make_unique<double[]>(n);
    for (int i = 0; i < n; i++) {
        signals_ptr[i] = signals[i];
    }
    
    // Лямбда: вычисление среднего значения
    auto mean = [](std::unique_ptr<double[]>& arr, int size) -> double {
        double sum = 0;
        for (int i = 0; i < size; i++) sum += arr[i];
        return sum / size;
    };
    
    // Лямбда: нормализация массива
    auto normalize = [](std::unique_ptr<double[]>& arr, int size, double max_val) {
        for (int i = 0; i < size; i++) arr[i] /= max_val;
    };
    
    // Лямбда: копирование обратно в вектор
    auto copyBack = [&](std::unique_ptr<double[]>& arr, int size) {
        for (int i = 0; i < size; i++) signals[i] = arr[i];
    };
    
    // Вычисления
    double avg = mean(signals_ptr, n);
    double max_val = *std::max_element(signals.begin(), signals.end());
    
    normalize(signals_ptr, n, max_val);
    copyBack(signals_ptr, n);
    
    // Вывод результатов
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Исходные данные: ";
    for (double val : signals) std::cout << val << " ";
    
    std::cout << std::endl << std::setprecision(3);
    std::cout << "Среднее значение: " << avg << std::endl;
    
    std::cout << "Нормализованные сигналы: ";
    for (double val : signals) std::cout << std::setprecision(3) << val << " ";
    
    return 0;
}