#include <iostream>

int main() 
{
    double arr[15];
    std::cout << "Введите " << 15 << " вещественных чисел:" << std::endl;
    for (int i = 0; i < 15; i++) {
        std::cout << "Элемент " << (i + 1) << ": ";
        std::cin >> arr[i];
    }
    
    int minIndex = 0;
    int maxIndex = 0;
    
    for (int i = 1; i < 15; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    
    std::cout << "Исходный массив:" << std::endl;
    for (int i = 0; i < 15; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    // Проверка условия и вычисление произведения
    if (maxIndex < minIndex) {
        std::cout << "Условие выполнено" << std::endl;
        
        double proisvedenie = arr[minIndex] * arr[maxIndex];
        
        std::cout << "Произведение минимального и максимального элементов: " << proisvedenie << std::endl;
        
    } 
    else {
        std::cout << "Условие не выполнено" << std::endl;
    }
    
    return 0;
}