#include <iostream>
#include <memory>
#include <iomanip>  // для std::setw

int main() {
    int N, M;
    std::cout << "Введите количество строк N: ";
    std::cin >> N;
    std::cout << "Введите количество столбцов M: ";
    std::cin >> M;
    
    // Создаем одномерный массив для хранения двумерной таблицы
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(N * M);
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            arr[i * M + j] = i * j;  // Формула для доступа к элементу [i][j]
        }
    }
    
    // Выводим результат в виде таблицы 
    std::cout << "\nТаблица произведений индексов (i * j):\n";
    std::cout << "     ";  // Отступ для заголовка столбцов
    
    // Выводим заголовки столбцов
    for (int j = 0; j < M; ++j) {
        std::cout << std::setw(4) << j;
    }
    std::cout << "\n    +";
    for (int j = 0; j < M; ++j) {
        std::cout << "----";
    }
    std::cout << std::endl;
    
    // Выводим строки таблицы
    for (int i = 0; i < N; ++i) {
        std::cout << std::setw(3) << i << " |";  // Заголовок строки
        for (int j = 0; j < M; ++j) {
            std::cout << std::setw(4) << arr[i * M + j];
        }
        std::cout << std::endl;
    }
    
    return 0;
}