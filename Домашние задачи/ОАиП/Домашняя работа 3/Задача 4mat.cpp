#include <iostream>

int main() 
{
    int N;
    std::cout << "Введите размер матрицы N( от 1 до 100): ";
    std::cin >> N;
    
    int matrix[N][N];
    int num = 1;       // Начинаем заполнение с числа 1
    int current_layer = 0;  // Текущий слой спирали (начинается с внешнего слоя)
    
    // Основной цикл для заполнения слоев спирали
    // Количество слоев = N/2 (для N=3 будет 1 слой, для N=4 - 2 слоя и т.д.)
    for (int k = 0; k < N / 2; k++) {
        // ПЕРВЫЙ ЦИКЛ: Заполнение ВЕРХНЕЙ СТРОКИ текущего слоя СЛЕВА НАПРАВО
        // matrix[current_layer][j] - строка current_layer фиксирована, j меняется от current_layer до N-current_layer-1
        for (int j = current_layer; j < N - current_layer; j++) {
            matrix[current_layer][j] = num;
            num++;
        }
        
        // ВТОРОЙ ЦИКЛ: Заполнение ПРАВОГО СТОЛБЦА текущего слоя СВЕРХУ ВНИЗ
        // matrix[i][N-1-current_layer] - столбец N-1-current_layer фиксирован, i меняется от current_layer+1 до N-current_layer-1
        for (int i = current_layer + 1; i < N - current_layer; i++) {
            matrix[i][N - 1 - current_layer] = num;
            num++;
        }
        
        // ТРЕТИЙ ЦИКЛ: Заполнение НИЖНЕЙ СТРОКИ текущего слоя СПРАВА НАЛЕВО
        // matrix[N-1-current_layer][N-j-1] - строка N-1-current_layer фиксирована, j меняется от current_layer+1 до N-current_layer-1 (в обратном порядке)
        for (int j = current_layer + 1; j < N - current_layer; j++) {
            matrix[N - 1 - current_layer][N - j - 1] = num;
            num++;
        }
        
        // ЧЕТВЕРТЫЙ ЦИКЛ: Заполнение ЛЕВОГО СТОЛБЦА текущего слоя СНИЗУ ВВЕРХ
        // matrix[N-i-1][current_layer] - столбец current_layer фиксирован, i меняется от current_layer+1 до N-current_layer-2 (в обратном порядке)
        for (int i = current_layer + 1; i < N - current_layer - 1; i++) {
            matrix[N - i - 1][current_layer] = num;
            num++;
        }
        
        current_layer++;
    }
    
    // Обработка центрального элемента для матриц с НЕЧЕТНЫМ размером
    if (N % 2 != 0) {
        matrix[N / 2][N / 2] = num;
    }

    std::cout << "Спиральная матрица:" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}