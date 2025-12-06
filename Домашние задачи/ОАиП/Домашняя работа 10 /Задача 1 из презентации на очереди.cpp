#include <iostream>
#include <queue>
#include <string>

void addToQueue(std::queue<std::string>& queue, const std::string& person) 
{
    queue.push(person);
}

void processQueue(std::queue<std::string>& queue) 
{
    if (queue.empty()) {
        std::cout << "Очередь пуста" << std::endl;
    } else {
        std::cout << "Первый человек обработан: " << queue.front() << std::endl;
        queue.pop();
    }
}

int main() 
{
    std::queue<std::string> supermarketQueue;
    
    // Тестирование функций
    addToQueue(supermarketQueue, "Иван");
    addToQueue(supermarketQueue, "Мария");
    addToQueue(supermarketQueue, "Петр");
    
    processQueue(supermarketQueue); // Обработает Ивана
    processQueue(supermarketQueue); // Обработает Марию
    processQueue(supermarketQueue); // Обработает Петра
    processQueue(supermarketQueue); // Выведет "Очередь пуста"
    
    return 0;
}