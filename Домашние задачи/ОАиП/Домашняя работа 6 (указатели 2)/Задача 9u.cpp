#include <iostream>

// Функция прямого прохода
double* forward(double** weights, double* inputs, int n, int m) 
{
    double* outputs = new double[n];
    
    for (int i = 0; i < n; i++) {
        outputs[i] = 0.0;
        for (int j = 0; j < m; j++) {
            outputs[i] += weights[i][j] * inputs[j];
        }
    }
    return outputs;
}

// Функция нормализации весов
void normalizeWeights(double** weights, int n, int m) 
{
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < m; j++) {
            sum += fabs(weights[i][j]);
        }
        if (sum > 1.0) {
            for (int j = 0; j < m; j++) {
                weights[i][j] /= sum;
            }
        }
    }
}

// Функция для вывода матрицы
void printMatrix(double** matrix, int n, int m) 
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

int main() 
{
    std::srand(std::time(0));
    
    int N, M;
    std::cout << "Введите количество нейронов (N) и количество входов (M): ";
    std::cin >> N >> M;
    
    // Создание матрицы весов
    double** weights = new double*[N];
    for (int i = 0; i < N; i++) {
        weights[i] = new double[M];
        for (int j = 0; j < M; j++) {
            // Инициализация случайными значениями от -1.0 до 1.0
            weights[i][j] = (double)rand() / RAND_MAX * 2.0 - 1.0;
        }
    }
    
    // Создание входного вектора
    double* inputs = new double[M];
    std::cout << "Введите " << M << " входных значений: ";
    for (int i = 0; i < M; i++) {
        std::cin >> inputs[i];
    }
    
    std::cout << "Исходная матрица весов:" << std::endl;
    printMatrix(weights, N, M);
    
    // Вычисление выходов
    double* outputs = forward(weights, inputs, N, M);
    
    std::cout << "Выходы нейронов до нормализации:" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << "Нейрон " << i << ": " << outputs[i] << std::endl;
    }
    
    // Нормализация весов
    normalizeWeights(weights, N, M);
    
    std::cout << "Матрица весов после нормализации:" << std::endl;
    printMatrix(weights, N, M);
    
    // Пересчет выходов после нормализации
    delete[] outputs;
    outputs = forward(weights, inputs, N, M);
    
    std::cout << "Выходы нейронов после нормализации:" << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << "Нейрон " << i << ": " << outputs[i] << std::endl;
    }
    
    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        delete[] weights[i];
    }
    delete[] weights;
    delete[] inputs;
    delete[] outputs;
    
    return 0;
}