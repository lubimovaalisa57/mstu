#include <iostream>
#include <memory>

int main() 
{
    int n;
    std::cin >> n;
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(n);  // Массив
    
    for (int i = 0; i < n; i++) 
        arr[i] = i + 1;  // Заполнение 1..N
    
    for (int i = 0; i < n; i++) 
        std::cout << arr[i] << " ";  // Вывод
    return 0;
}