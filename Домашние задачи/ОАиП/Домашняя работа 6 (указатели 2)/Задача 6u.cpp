#include <iostream>

// Функция для вычисления суммы элементов через указатели
int sumElements(int **arr, int n, int m) 
{
    int sum = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // Доступ к элементу через арифметику указателей
            sum += *(*(arr + i) + j);
        }
    }
    return sum;
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
    int n = 3, m = 5;
    
    // Создаем двумерный массив
    int **arr = new int*[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new int[m];
    }
    
    // Заполняем массив вручную
    std::cout << "Введите элементы матрицы " << n << "x" << m << ":" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << "Строка " << i + 1 << ": ";
        for (int j = 0; j < m; ++j) {
            std::cin >> *(*(arr + i) + j);  // ввод через указатели
        }
    }
    
    // Выводим массив для проверки
    std::cout << "Введенная матрица:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << *(*(arr + i) + j) << " ";  // вывод через указатели
        }
        std::cout << std::endl;
    }
    
    // Вычисляем сумму через указатели
    int total = sumElements(arr, n, m);
    std::cout << "Сумма всех элементов: " << total << std::endl;
    
    free2D(arr, n);
    
    return 0;
}