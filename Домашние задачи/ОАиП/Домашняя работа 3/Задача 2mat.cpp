#include <iostream>

int main() {
    int N;
    std::cout << "Введите размер матрицы N от 1 до 50: ";
    std::cin >> N;
    
    int matrix[N][N];
    std::cout << "Введите матрицу " << N << "x" << N << ":" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> matrix[i][j];
        }
    }
    // Вычисляем сумму первой строки - эталонную сумму
    int first_sum = 0;
    for (int j = 0; j < N; j++) {
        first_sum += matrix[0][j];
    }
    
    

    // Проверяем суммы всех остальных строк
    bool is_magic1= true;
    for (int i = 1; i < N; i++) {
        int row_sum = 0; // Сумма текущей строки
        for (int j = 0; j < N; j++) {
            row_sum += matrix[i][j];
        }
        if (row_sum != first_sum) {
            is_magic1 = false;
        }
    }
    
    // Проверяем суммы всех столбцов
    bool is_magic2 = true;
    for (int j = 0; j < N; j++) {
        int col_sum = 0; // Сумма текущего столбца
        for (int i = 0; i < N; i++) {
            col_sum += matrix[i][j];
        }
        if (col_sum != first_sum) {
            is_magic2 = false;
        }
    }
    
    // Проверяем сумму главной диагонали (слева направо)
    bool is_magic3 = true;
    int diag1 = 0;
    for (int i = 0; i < N; i++) {
        diag1 += matrix[i][i];
    }
    if (diag1 != first_sum) {
        is_magic3 = false;
    }
    
    // Проверяем сумму побочной диагонали (справа налево)
    bool is_magic4 = true;
    int diag2 = 0;
    for (int i = 0; i < N; i++) {
        diag2 += matrix[i][N-1-i];
    }
    if (diag2 != first_sum) {
        is_magic4 = false;
    }
    
    if (is_magic1 == true,  is_magic2 == true, is_magic3 == true, is_magic4 == true) {
        std::cout << "YES " << first_sum << std::endl;
    } 
    else {
        std::cout << "NO" << std::endl;
    }
    
    return 0;
}