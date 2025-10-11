#include <iostream>

int main() 
{
    int N;
    std::cout << "Введите размер матрицы N от 1 до 100: ";
    std::cin >> N;
    
    int matrix[N][N];
    std::cout << "Введите матрицу " << N << "x" << N << ":" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> matrix[i][j];
        }
    }
    
    // Создаем 4 матрицы для отражений
    int main_diag[N][N], side_diag[N][N];
    int vertical[N][N], horizontal[N][N];
    
    // Заполняем матрицы отражений
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Отражение относительно главной диагонали
            main_diag[i][j] = matrix[j][i];
            
            // Отражение относительно побочной диагонали
            side_diag[i][j] = matrix[N-1-j][N-1-i];
            
            // Зеркальное отражение по вертикали
            vertical[i][j] = matrix[i][N-1-j];
            
            // Зеркальное отражение по горизонтали
            horizontal[i][j] = matrix[N-1-i][j];
        }
    }
    
    // Вывод всех матриц
    std::cout << "Отражение относительно главной диагонали:" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << main_diag[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "Отражение относительно побочной диагонали:" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << side_diag[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "Зеркальное отражение по вертикали:" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << vertical[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "Зеркальное отражение по горизонтали:" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << horizontal[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    // Сравнение матриц
    bool found_match = false;
    
    // Сравниваем попарно все матрицы
    if (N > 0) {
        // Сравнение 1 и 2 (главная и побочная диагонали)
        bool match12 = true;
        for (int i = 0; i < N && match12; i++) {
            for (int j = 0; j < N && match12; j++) {
                if (main_diag[i][j] != side_diag[i][j]) {
                    match12 = false;
                }
            }
        }
        if (match12=true) {
            std::cout << "(1, 2)" << std::endl;
            found_match = true;
        }
        
        // Сравнение 1 и 3 (главная диагональ и вертикаль)
        bool match13 = true;
        for (int i = 0; i < N && match13; i++) {
            for (int j = 0; j < N && match13; j++) {
                if (main_diag[i][j] != vertical[i][j]) {
                    match13 = false;
                }
            }
        }
        if (match13 = true) {
            std::cout << "(1, 3)" << std::endl;
            found_match = true;
        }
        
        // Сравнение 1 и 4 (главная диагональ и горизонталь)
        bool match14 = true;
        for (int i = 0; i < N && match14; i++) {
            for (int j = 0; j < N && match14; j++) {
                if (main_diag[i][j] != horizontal[i][j]) {
                    match14 = false;
                }
            }
        }
        if (match14 = true) {
            std::cout << "(1, 4)" << std::endl;
            found_match = true;
        }
        
        // Сравнение 2 и 3 (побочная диагональ и вертикаль)
        bool match23 = true;
        for (int i = 0; i < N && match23; i++) {
            for (int j = 0; j < N && match23; j++) {
                if (side_diag[i][j] != vertical[i][j]) {
                    match23 = false;
                }
            }
        }
        if (match23 = true) {
            std::cout << "(2, 3)" << std::endl;
            found_match = true;
        }
        
        // Сравнение 2 и 4 (побочная диагональ и горизонталь)
        bool match24 = true;
        for (int i = 0; i < N && match24; i++) {
            for (int j = 0; j < N && match24; j++) {
                if (side_diag[i][j] != horizontal[i][j]) {
                    match24 = false;
                }
            }
        }
        if (match24 = true) {
            std::cout << "(2, 4)" << std::endl;
            found_match = true;
        }
        
        // Сравнение 3 и 4 (вертикаль и горизонталь)
        bool match34 = true;
        for (int i = 0; i < N && match34; i++) {
            for (int j = 0; j < N && match34; j++) {
                if (vertical[i][j] != horizontal[i][j]) {
                    match34 = false;
                }
            }
        }
        if (match34 = true) {
            std::cout << "(3, 4)" << std::endl;
            found_match = true;
        }
    }
    
    if (found_match = true) {
        std::cout << "NONE" << std::endl;
    }
    
    return 0;
}