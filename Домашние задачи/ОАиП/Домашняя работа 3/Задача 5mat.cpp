#include <iostream>

int main() 
{
    int N, M;
    std::cout << "Введите размеры матрицы N и M : ";
    std::cin >> N >> M;
    
    int matrix[N][M];
    std::cout << "Введите матрицу " << N << "x" << M << ":" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cin >> matrix[i][j];
        }
    }
    
    // Переменная current_layer отслеживает текущий слой спирали
    int current_layer = 0;
    
    // Основной цикл для обхода спирали по слоям
    // Условие j < N/2 && j < M/2 ограничивает количество слоев
    for (int k = 0; k < N / 2 && k < M / 2; k++) {
        // Первый цикл: обход ВЕРХНЕЙ СТРОКИ текущего слоя слева направо
        // matrix[current_layer][i] - строка current_layer фиксирована, столбец i меняется от current_layer до M-current_layer-1
        for (int j = current_layer; j < M - current_layer; j++) {
            std::cout << matrix[current_layer][j] << " ";
        }
        
        // Второй цикл: обход ПРАВОГО СТОЛБЦА текущего слоя сверху вниз
        // matrix[i][M-1-current_layer] - столбец M-1-current_layer фиксирован, строка i меняется от current_layer+1 до N-current_layer-1
        for (int i = current_layer + 1; i < N - current_layer; i++) {
            std::cout << matrix[i][M - 1 - current_layer] << " ";
        }
        
        // Третий цикл: обход НИЖНЕЙ СТРОКИ текущего слоя справа налево
        // matrix[N-1-current_layer][M-j-1] - строка N-1-current_layer фиксирована, столбец меняется в обратном порядке
        for (int j = current_layer + 1; j < M - current_layer; j++) {
            std::cout << matrix[N - 1 - current_layer][M - j - 1] << " ";
        }
        
        // Четвертый цикл: обход ЛЕВОГО СТОЛБЦА текущего слоя снизу вверх
        // matrix[N-i-1][current_layer] - столбец current_layer фиксирован, строка меняется в обратном порядке
        for (int i = current_layer + 1; i < N - current_layer - 1; i++) {
            std::cout << matrix[N - i - 1][current_layer] << " ";
        }
        
        // Переход к следующему слою спирали
        current_layer++;
    }
    
    // Обработка центрального элемента для квадратных матриц с нечетными размерами
    // Условие: матрица должна быть квадратной (N == M) и иметь нечетные размеры
    if (N % 2 != 0 && M % 2 != 0 && N == M) {
        std::cout << matrix[N / 2][M / 2] << " " << std::endl;
    }
    
    return 0;
}