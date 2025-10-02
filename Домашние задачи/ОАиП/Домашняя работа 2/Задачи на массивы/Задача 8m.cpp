#include <iostream>

int main() 
{
    int arr[10];
    
    std::cout << "Введите " << 10 << " целых чисел:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "Элемент " << (i + 1) << ": ";
        std::cin >> arr[i];
    }
    
    // Поиск индексов минимального и максимального элементов
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
    
    // Вывод исходного массива
    std::cout << "Исходный массив:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Проверка условий и выполнение преобразования
    if (maxIndex == 1 && minIndex == 4) { 
        int maxElement = arr[maxIndex];
        
        // Установка всех элементов от минимального до конца равными максимальному
        for (int i = minIndex; i < 10; i++) {
            arr[i] = maxElement;
        }
        
        std::cout << "Условие выполнено. Преобразованный массив:" << std::endl;
        for (int i = 0; i < 10; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        
    }
    else {
        std::cout << "Условие не выполнено. Массив остается без изменений" << std::endl;
    }
    
    return 0;
}