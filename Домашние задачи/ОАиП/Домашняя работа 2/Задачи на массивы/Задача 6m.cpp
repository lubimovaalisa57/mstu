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
    
    // Вывод исходного массива
    std::cout << "Исходный массив:" << std::endl;
    for (int i = 0; i < 15; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    
    if (minIndex == 1 && maxIndex == 0) {
        for (int i = 0; i < 15; i++) {
            arr[i] /= 2.0;
        }
        
        std::cout << "Условие выполнено. Преобразованный массив:" << std::endl;
        for (int i = 0; i < 15; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        
    } else {
        std::cout << "Условие не выполнено. Массив остается без изменений." << std::endl;
    }
    
    return 0;
}