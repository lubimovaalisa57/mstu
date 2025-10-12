#include <iostream>

int main() {
    int N;
    std::cout << "Введите размер матрицы N от 1 до 100: ";
    std::cin >> N;
    
    int matrix[N][N] = {0};
    
    int num = 1;
    int top = 0, bottom = N - 1;
    int left = 0, right = N - 1;
    
    while (num <= N * N) {
        // Заполняем верхнюю строку слева направо
        for (int j = left; j <= right; j++) {
            matrix[top][j] = num;
            num++;
        }
        top++;
        
        // Заполняем правый столбец сверху вниз
        for (int i = top; i <= bottom; i++) {
            matrix[i][right] = num;
            num++;
        }
        right--;
        
        // Заполняем нижнюю строку справа налево
        for (int j = right; j >= left; j--) {
            matrix[bottom][j] = num;
            num++;
        }
        bottom--;
        
        // Заполняем левый столбец снизу вверх
        for (int i = bottom; i >= top; i--) {
            matrix[i][left] = num;
            num++;
        }
        left++;
    }
    
    // Вывод матрицы
    std::cout << "Спиральная матрица:" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}