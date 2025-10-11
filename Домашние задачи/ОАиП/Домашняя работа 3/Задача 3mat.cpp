#include <iostream>

int main() {
    int N, M;
    std::cout << "Введите размеры матрицы N(>=1) и M(<=100) : ";
    std::cin >> N >> M;
    
    int matrix[N][M];
    std::cout << "Введите матрицу " << N << "x" << M << ":" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cin >> matrix[i][j];
        }
    }
    
    int row_min[N], row_max[N];
    int col_min[M], col_max[M];
    
    for (int i = 0; i < N; i++) {
        row_min[i] = matrix[i][0];
        row_max[i] = matrix[i][0];
    }
    
    for (int j = 0; j < M; j++) {
        col_min[j] = matrix[0][j];
        col_max[j] = matrix[0][j];
    }
    
     // Вычисление минимумов и максимумов для каждой строки
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (matrix[i][j] < row_min[i]) {
                row_min[i] = matrix[i][j];
            }
            if (matrix[i][j] > row_max[i]) {
                row_max[i] = matrix[i][j];
            }
        }
    }
    
    // Вычисление минимумов и максимумов для каждого столбца
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < N; i++) {
            if (matrix[i][j] < col_min[j]) {
                col_min[j] = matrix[i][j];
            }
            if (matrix[i][j] > col_max[j]) {
                col_max[j] = matrix[i][j];
            }
        }
    }
    
    bool found_A = false;
    bool found_B = false;
    
    // Поиск седловых точек в матрице
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // Проверка на тип A: максимален в строке и минимален в столбце
            if (matrix[i][j] == row_max[i] && matrix[i][j] == col_min[j]) {
                std::cout << "А " << matrix[i][j] << " " << i+1 << " " << j+1 << std::endl;
                found_A = true;
            }
            // Проверка на тип B: минимален в строке и максимален в столбце
            if (matrix[i][j] == row_min[i] && matrix[i][j] == col_max[j]) {
                std::cout << "B " << matrix[i][j] << " " << i+1 << " " << j+1 << std::endl;
                found_B = true;
            }
        }
    }
    
    if (found_A == false && found_B == false) {
        std::cout << "NONE" << std::endl;
    }
    
    return 0;
}