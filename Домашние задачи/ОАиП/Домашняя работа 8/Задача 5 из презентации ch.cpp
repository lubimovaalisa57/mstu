#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

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
    std::vector<int> arr(SIZE);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 10000);
    
    for (int i = 0; i < SIZE; i++) {
        arr[i] = dist(gen);
    }
    
    // Bubble Sort
    std::vector<int> arr1 = arr;
    auto start1 = std::chrono::high_resolution_clock::now();
    bubbleSort(arr1);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    
    // Insertion Sort
    std::vector<int> arr2 = arr;
    auto start2 = std::chrono::high_resolution_clock::now();
    insertionSort(arr2);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
    
    // std::sort
    std::vector<int> arr3 = arr;
    auto start3 = std::chrono::high_resolution_clock::now();
    std::sort(arr3.begin(), arr3.end());
    auto end3 = std::chrono::high_resolution_clock::now();
    auto time3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3);
    
    std::cout << "Bubble Sort: " << time1.count() << " ms" << std::endl;
    std::cout << "Insertion Sort: " << time2.count() << " ms" << std::endl;
    std::cout << "std::sort: " << time3.count() << " ms" << std::endl;
    
    return 0;
}