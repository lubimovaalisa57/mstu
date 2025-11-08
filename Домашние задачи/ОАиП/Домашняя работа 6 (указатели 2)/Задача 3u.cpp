#include <iostream>

// Функция для освобождения памяти двумерного массива
void free2D(int **arr, int n) 
{
    for (int i = 0; i < n; ++i) {
        delete[] arr[i];  // освобождаем память каждой строки
    }
    delete[] arr;  // освобождаем массив указателей
}

int main() 
{
    std::srand(std::time(0));
    
    int n, m;
    std::cout << "Введите n и m: ";
    std::cin >> n >> m;
    
    int **arr = new int*[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new int[m];
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            arr[i][j] = rand() % 100;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    // Используем нашу функцию для освобождения памяти
    free2D(arr, n);
    
    return 0;
}