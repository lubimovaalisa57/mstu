#include <iostream>

int main() 
{
    int arr[10];
    std::cout << "Введите " << 10 << " целых чисел:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "Элемент " << (i + 1) << ": ";
        std::cin >> arr[i];
    }
    
    int minIndex = 0;
    int maxIndex = 0;
    
    for (int i = 1; i < 10; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    
    std::cout << "Исходный массив:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    

    if (minIndex == 4 && maxIndex == 9) { 
        std::cout << "Условие выполнено" << std::endl;
        
        double average = (arr[minIndex] + arr[maxIndex]) / 2.0;
        
        std::cout << "Среднее арифметическое минимального и максимального элементов: " << average << std::endl;
    } 
    else {
        std::cout << "Условие не выполнено" << std::endl;
    }
    
    return 0;
}