#include <iostream>
#include <memory>

int main() 
{
    int N;
    std::cout << "Введите размер массива: ";
    std::cin >> N;
    
    // Создаем умный указатель на массив 
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(N);
    
    for (int i = 0; i < N; ++i) {
        arr[i] = i + 1;
    }
    
    std::cout << "Содержимое массива: " << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    
    return 0;
}