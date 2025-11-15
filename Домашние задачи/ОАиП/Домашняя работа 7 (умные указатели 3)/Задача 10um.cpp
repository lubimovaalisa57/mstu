#include <iostream>
#include <memory>

// Функция создает и возвращает unique_ptr массив
std::unique_ptr<int[]> createArray(int n) 
{
    auto arr = std::make_unique<int[]>(n);  // Создание массива
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;  // Заполнение 1..n
    }
    return arr;  // Возврат владения
}

int main() 
{
    int n;
    std::cin >> n;
    
    auto arr = createArray(n);  // Прием владения
    
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";  // Вывод элементов
    }
    return 0;
}