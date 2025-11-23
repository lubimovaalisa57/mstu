#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// Пузырьковая сортировка
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Сортировка вставками
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    const int SIZE = 10000;
    std::vector<int> original(SIZE);
    
    // Заполняем массив случайными числами
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 10000);
    
    for (int i = 0; i < SIZE; i++) {
        original[i] = dist(gen);
    }
    
    // Тестируем пузырьковую сортировку
    std::vector<int> arr1 = original;
    auto start1 = std::chrono::high_resolution_clock::now();
    bubbleSort(arr1);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    
    // Тестируем сортировку вставками
    std::vector<int> arr2 = original;
    auto start2 = std::chrono::high_resolution_clock::now();
    insertionSort(arr2);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start1);
    
    // Тестируем std::sort
    std::vector<int> arr3 = original;
    auto start3 = std::chrono::high_resolution_clock::now();
    std::sort(arr3.begin(), arr3.end());
    auto end3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3);
    
    // Выводим результаты
    std::cout << "Сравнение времени сортировки (массив из " << SIZE << " элементов):" << std::endl;
    std::cout << "Пузырьковая сортировка: " << duration1.count() << " мс" << std::endl;
    std::cout << "Сортировка вставками: " << duration2.count() << " мс" << std::endl;
    std::cout << "std::sort: " << duration3.count() << " мс" << std::endl;
    
    return 0;
}