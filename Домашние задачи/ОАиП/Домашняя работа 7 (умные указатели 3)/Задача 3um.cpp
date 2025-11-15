#include <iostream>
#include <memory>

// Функция заполнения массива квадратами индексов
void fillArray(std::unique_ptr<int[]>& arr, int n) 
{
    for (int i = 0; i < n; ++i) {
        arr[i] = i * i;  // Заполняем квадратами индексов
    }
}

int main() 
{
    int n;
    std::cout << "Введите размер массива: ";
    std::cin >> n;
    
    // Создаем умный указатель на массив
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(n);
    
    // Передаем массив по ссылке в функцию для заполнения
    fillArray(arr, n);
    
    std::cout << "Массив квадратов индексов: " << std::endl;;
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    
    return 0;
}