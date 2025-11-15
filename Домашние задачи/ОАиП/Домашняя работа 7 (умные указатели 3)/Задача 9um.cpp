#include <iostream>
#include <memory>
#include <vector>

// Функция A: увеличивает все элементы на 1
void processA(std::shared_ptr<std::vector<int>> buf) 
{
    for (auto& num : *buf) num += 1;
}

// Функция B: умножает все элементы на 2
void processB(std::shared_ptr<std::vector<int>> buf) 
{
    for (auto& num : *buf) num *= 2;
}

int main() 
{
    // Создание общего буфера
    auto buffer = std::make_shared<std::vector<int>>();
    
    for (int i = 1; i <= 10; i++) {
        buffer->push_back(i);
    }
    
    // Вызов функций
    processA(buffer);  // Увеличить на 1
    processB(buffer);  // Умножить на 2
    
    for (int num : *buffer) {
        std::cout << num << " ";
    }
    return 0;
}