#include <iostream>

int main() 
{
    double arr[15];

    std::cout << "Введите " << 15 << " вещественных чисел:" << std::endl;
    
    for (int i = 0; i < 15; i++) {
        std::cout << "Число " << (i + 1) << ": ";
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
    
    // Вывод исходной последовательности
    std::cout << "Исходная последовательность:" << std::endl;
    for (int i = 0; i < 15; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    // Обмен наименьшего числа с первым
    double temp = arr[0];
    arr[0] = arr[minIndex];
    arr[minIndex] = temp;
    
    // Обмен наибольшего числа с последним
    temp = arr[15 - 1];
    arr[15 - 1] = arr[maxIndex];

    // Вывод преобразованной последовательности
    std::cout << "Преобразованная последовательность:" << std::endl;
    for (int i = 0; i < 15; i++) {
        std::cout << arr[i] << " ";
    }
std::cout << std::endl;
    
    return 0;
}