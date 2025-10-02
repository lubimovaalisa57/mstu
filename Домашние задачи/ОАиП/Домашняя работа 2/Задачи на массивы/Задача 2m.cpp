#include <iostream>

int main() 
{
    const int MAX_SIZE = 1000; // Максимально возможный размер
    int n;
    std::cout << "Введите количество чисел n: ";
    std::cin >> n;

    if (n <= 0 || n > MAX_SIZE) {
        std::cout << "Ошибка: n должно быть натуральным числом не больше " << MAX_SIZE << std::endl;
        return 1;
    }
    
    int numbers[MAX_SIZE]; // Замена вектора на обычный массив
    
    // Ввод последовательности чисел
    std::cout << "Введите " << n << " целых чисел:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "A" << (i + 1) << " = ";
        std::cin >> numbers[i];
    }
    
    // Инициализация переменных
    int maxNechet = 0;
    int СountChet = 0;    // Счетчик четных чисел
    
    // Обработка последовательности
    for (int i = 0; i < n; i++) {
        int current = numbers[i];
        
        
        if (current % 2 == 0) {
            СountChet++;
        } 
        
        else if (current % 2 != 0) {
            if (current > maxNechet) {
                maxNechet = current;
            }
        }
    }
    
    if (maxNechet != 0) {
        std::cout << "Наибольшее нечетное число: " << maxNechet << std::endl;
    } else {
        std::cout << "Нечетных чисел в последовательности нет" << std::endl;
    }
     std::cout << "Количество четных чисел: " << СountChet << std::endl;
    
    return 0;
}