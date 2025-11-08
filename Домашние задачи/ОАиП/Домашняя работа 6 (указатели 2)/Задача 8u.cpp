#include <iostream>

// Выделение памяти для пластины N x M
double **allocatePlate(int n, int m) 
{
    double **plate = new double*[n];
    for (int i = 0; i < n; i++) {
        plate[i] = new double[m];
    }
    return plate;
}

// Освобождение памяти пластины
void freePlate(double **plate, int n) 
{
    for (int i = 0; i < n; i++) {
        delete[] plate[i];
    }
    delete[] plate;
}

// Обновление температур на пластине
void updateTemperature(double **plate, int n, int m) 
{
    // Создаем временный массив для новых температур
    double **newPlate = allocatePlate(n, m);
    
    // Копируем текущие температуры
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            newPlate[i][j] = plate[i][j];
        }
    }
    
    // Обновляем температуры (кроме границ и центрального нагревателя)
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < m - 1; j++) {
            // Пропускаем нагреватель в центре
            if (i == n/2 && j == m/2) continue;
            
            // Среднее арифметическое четырех соседей
            newPlate[i][j] = (plate[i-1][j] + plate[i+1][j] + 
                             plate[i][j-1] + plate[i][j+1]) / 4.0;
        }
    }
    
    // Копируем новые температуры обратно в основную пластину
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            plate[i][j] = newPlate[i][j];
        }
    }
    
    // Восстанавливаем температуру нагревателя в центре
    plate[n/2][m/2] = 100.0;
    
    freePlate(newPlate, n);
}

int main() 
{
    int N, M, K;
    std::cout << "Введите размеры пластины (N M): ";
    std::cin >> N >> M;
    std::cout << "Введите количество итераций: ";
    std::cin >> K;
    
    // Создание и инициализация пластины
    double **plate = allocatePlate(N, M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            plate[i][j] = 20.0;  // Начальная температура 20°C
        }
    }
    
    // Установка нагревателя в центре
    plate[N/2][M/2] = 100.0;
    
    // Итерации распространения тепла
    for (int k = 0; k < K; k++) {
        updateTemperature(plate, N, M);
    }
    
    // Вывод финального распределения температур
    std::cout << "Финальное распределение температуры:" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cout << plate[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    freePlate(plate, N);
    return 0;
}