#include <iostream>

// Вычисление средней нагрузки каждого узла
double *averageLoadPerNode(int **load, int n, int t) 
{
    double *averages = new double[n];
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < t; j++) {
            sum += *(*(load + i) + j);  // Арифметика указателей
        }
        averages[i] = (double)sum / t;
    }
    return averages;
}

// Нормализация нагрузки между узлами
void normalizeLoad(int **load, int n, int t) 
{
    double *averages = averageLoadPerNode(load, n, t);
    for (int i = 0; i < n; i++) {
        if (averages[i] > 80.0) {  // Проверка превышения 80%
            for (int j = 0; j < t; j++) {
                if (*(*(load + i) + j) > 80) {
                    // Перераспределение 10% нагрузки
                    int redistribute = std::round(*(*(load + i) + j) * 0.1);
                    int receivers = n - 1;
                    if (receivers > 0) {
                        int perReceiver = redistribute / receivers;
                        *(*(load + i) + j) -= redistribute;
                        // Распределение по другим узлам
                        for (int k = 0; k < n; k++) {
                            if (k != i) *(*(load + k) + j) += perReceiver;
                        }
                    }
                }
            }
        }
    }
    delete[] averages;
}

// Поиск интервала с максимальной суммарной нагрузкой
int findCriticalInterval(int **load, int n, int t) 
{
    int maxSum = 0, critical = 0;
    for (int j = 0; j < t; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += *(*(load + i) + j);  // Арифметика указателей
        }
        if (sum > maxSum) {
            maxSum = sum;
            critical = j;
        }
    }
    return critical;
}

// Вывод матрицы нагрузок
void printMatrix(int **load, int n, int t) 
{
    for (int i = 0; i < n; i++) {
        std::cout << "Узел " << i << ": ";
        for (int j = 0; j < t; j++) {
            std::cout << *(*(load + i) + j) << "% ";
        }
        std::cout << std::endl;
    }
}

int main() 
{
    int n, t;
    std::cout << "Введите количество узлов и интервалов: ";
    std::cin >> n >> t;
    
    // Создание матрицы нагрузок
    int **load = new int*[n];
    for (int i = 0; i < n; i++) {
        load[i] = new int[t];
    }
    
    // Ввод данных
    std::cout << "Введите нагрузку для каждого узла по интервалам: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Узел " << i << ": ";
        for (int j = 0; j < t; j++) {
            int value;
            std::cin >> value;
            if (value < 0 || value > 100) {
                std::cout << "Ошибка: нагрузка должна быть 0-100% " << std::endl;
                return 1;
            }
            *(*(load + i) + j) = value;
        }
    }
    
    // Вывод исходных данных
    std::cout << "Исходная матрица: " << std::endl;
    printMatrix(load, n, t);
    
    // Средние нагрузки
    double *avg = averageLoadPerNode(load, n, t);
    std::cout << "Средние нагрузки: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Узел " << i << ": " << avg[i] << "%" << std::endl;
    }
    
    // Нормализация
    normalizeLoad(load, n, t);
    
    // Результаты после нормализации
    std::cout << "После нормализации: " << std::endl;
    printMatrix(load, n, t);
    
    // Критический интервал
    int critical = findCriticalInterval(load, n, t);
    int sumCritical = 0;
    for (int i = 0; i < n; i++) {
        sumCritical += *(*(load + i) + critical);
    }
    std::cout << "Критический интервал: " << critical << " (суммарная нагрузка = " << sumCritical << "%)" << std::endl;
    
    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        delete[] load[i];
    }
    delete[] load;
    delete[] avg;
    
    return 0;
}