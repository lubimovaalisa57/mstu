#include <iostream>

// Функция для транспонирования матрицы
int **transpose(int **matrix, int n, int m) 
{
    // Создаем новую матрицу с размерами m x n (меняем местами)
    int **result = new int*[m];
    for (int i = 0; i < m; ++i) {
        result[i] = new int[n];
    }
    
    // Заполняем транспонированную матрицу
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = matrix[j][i];  // меняем индексы местами
        }
    }
    
    return result;
}

// Функция для вывода матрицы
void printMatrix(int **matrix, int n, int m) 
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Функция для освобождения памяти
void free2D(int **arr, int n) 
{
    for (int i = 0; i < n; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

int main() 
{
    int n = 3, m = 4;
    
    // Создаем исходную матрицу
    int **matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[m];
    }
    
    // Заполняем исходную матрицу значениями
    int value = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = value++;
        }
    }
    
    std::cout << "Исходная матрица " << n << "x" << m << ": " << std::endl;
    printMatrix(matrix, n, m);
    
    // Транспонируем матрицу
    int **transposed = transpose(matrix, n, m);
    
    std::cout << "Транспонированная матрица " << m << "x" << n << ": " << std::endl;
    printMatrix(transposed, m, n);
    
    // Освобождаем память
    free2D(matrix, n);
    free2D(transposed, m);
    
    return 0;
}