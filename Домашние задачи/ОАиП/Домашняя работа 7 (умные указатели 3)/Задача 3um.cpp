#include <iostream>
#include <memory>

void fillArray(std::unique_ptr<int[]>& arr, int n) 
{
    for (int i = 0; i < n; i++)
        arr[i] = i * i;  // Квадраты индексов
}

int main() 
{
    int n;
    std::cin >> n;
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(n);
    fillArray(arr, n);  // Передача по ссылке
    
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    return 0;
}