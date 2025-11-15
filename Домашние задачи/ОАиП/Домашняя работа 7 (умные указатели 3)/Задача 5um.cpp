#include <iostream>
#include <memory>

int main() 
{
    int n, m;
    std::cin >> n >> m;
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(n * m);
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            arr[i * m + j] = i * j;  // Заполнение произведениями
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            std::cout << arr[i * m + j] << "\t";  // Вывод таблицы
        std::cout << std::endl;
    }
    return 0;
}