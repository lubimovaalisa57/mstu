#include <iostream>

// Функция для вычисления суммы элементов строки
int rowSum(int *row, int m) 
{
    int sum = 0;
    for (int j = 0; j < m; ++j) {
        sum += row[j];
    }
    return sum;
}

// Функция для сортировки строк по сумме элементов
void sortRowsBySum(int **arr, int n, int m) 
{
    // Создаем массив для хранения сумм строк
    int *sums = new int[n];
    for (int i = 0; i < n; ++i) {
        sums[i] = rowSum(arr[i], m);
    }
    
    // Сортировка пузырьком (меняем указатели на строки)
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (sums[j] > sums[j + 1]) {
                // Меняем местами указатели на строки
                int *tempPtr = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tempPtr;
                
                // Меняем местами суммы
                int tempSum = sums[j];
                sums[j] = sums[j + 1];
                sums[j + 1] = tempSum;
            }
        }
    }
    
    delete[] sums;
}

// Функция для вывода матрицы с суммами строк
void printMatrixWithSums(int **arr, int n, int m) 
{
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < m; ++j) {
            std::cout << arr[i][j] << " ";
            sum += arr[i][j];
        }
        std::cout << "| sum = " << sum << std::endl;
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
    std::srand(std::time(0));
    
    int n = 4, m = 3;
    
    // Создаем и заполняем массив случайными числами
    int **arr = new int*[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new int[m];
        for (int j = 0; j < m; ++j) {
            arr[i][j] = rand() % 10;  // числа от 0 до 9 для наглядности
        }
    }
    
    std::cout << "Исходный массив:" << std::endl;
    printMatrixWithSums(arr, n, m);
    
    // Сортируем строки по сумме элементов
    sortRowsBySum(arr, n, m);
    
    std::cout << "После сортировки по сумме:" << std::endl;
    printMatrixWithSums(arr, n, m);
    
    free2D(arr, n);
    
    return 0;
}