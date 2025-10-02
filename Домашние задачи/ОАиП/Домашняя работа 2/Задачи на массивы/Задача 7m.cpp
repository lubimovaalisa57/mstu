#include <iostream>

int main() 
{
    int arr[15];
    
    std::cout << "Введите " << 15 << " целых чисел:" << std::endl;
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
    
    if (arr[minIndex] == 0 || arr[maxIndex] == 0) {
        std::cout << "Условие выполнено ";
        
        // Обнуление элементов, предшествующих минимальному
        for (int i = 0; i < minIndex; i++) {
            arr[i] = 0;
        }
        
        std::cout << "Преобразованный массив:  " << std::endl;
        for (int i = 0; i < 15; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        
    } 
    else {
        std::cout << "Условие не выполнено. Массив остается без изменени" << std::endl;
    }
    return 0;
}