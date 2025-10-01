#include <iostream>

int main() {
    int n;
    std::cin >> n;
    
    if (n <= 0) {
        std::cout << "Ошибка: n должно быть натуральным числом" << std::endl;
        return 1;
    }
    
    int arr[n]; 
    
    std::cout << "Введите последовательность из " << n << " натуральных чисел:" << std::endl;

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
        if (arr[i] <= 0) {
            std::cout << "Ошибка: все числа должны быть натуральными!" << std::endl;
            return 1;
        }
    }
    
    // Подсчет чисел, удовлетворяющих условию
    int result = 0;
    
    for (int k = 0; k < n; k++) {
        // Условие: A[k] > 2*(k+1) т.к. нумерация с 1
        if (arr[k] > 2 * (k + 1)) {
            result++;
        }
    }
    
    std::cout << "Количество чисел, удовлетворяющих условию Ak > 2k: " << result << std::endl;
    
    return 0;
}
