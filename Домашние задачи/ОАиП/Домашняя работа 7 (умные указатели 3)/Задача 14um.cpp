#include <iostream>
#include <memory>
#include <vector>

int main() 
{
    int n, m;
    std::cout << "Введите N и M: ";
    std::cin >> n >> m;
    
    auto matrix = std::make_unique<double[]>(n * m);
    
    // Заполнение матрицы
    std::cout << "Введите элементы матрицы:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> matrix[i * m + j];
        }
    }
    
    // Лямбда для сумм столбцов
    auto sumColumns = [&]() -> std::vector<double> {
        std::vector<double> sums(m, 0.0);
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                sums[j] += matrix[i * m + j];
            }
        }
        return sums;
    };
    
    // Лямбда для индекса максимального столбца
    auto maxIndex = [](const std::vector<double>& sums) -> int {
        int max_idx = 0;
        for (int i = 1; i < sums.size(); i++) {
            if (sums[i] > sums[max_idx]) max_idx = i;
        }
        return max_idx;
    };
    
    // Вычисления
    auto sums = sumColumns();
    int max_col = maxIndex(sums);
    
    // Вывод результатов
    std::cout << "Суммы столбцов: [";
    for (int i = 0; i < m; i++) {
        std::cout << sums[i];
        if (i < m - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    
    std::cout << "Столбец с максимальной суммой: " << max_col + 1 
              << " (" << sums[max_col] << ")" << std::endl;
    
    return 0;
}