#include <iostream>
#include <queue>
#include <string>

void addEvent(std::queue<std::string>& eventQueue, const std::string& event) 
{
    eventQueue.push(event);
    std::cout << "Добавлено событие: " << event << std::endl;
}

void processEvents(std::queue<std::string>& eventQueue) 
{
    if (eventQueue.empty()) {
        std::cout << "Очередь событий пуста" << std::endl;
    } else {
        std::cout << "Обрабатывается событие: " << eventQueue.front() << std::endl;
        eventQueue.pop();
    }
}

int main() 
{
    std::queue<std::string> eventQueue;
    
    // Тестирование функций
    addEvent(eventQueue, "Запрос от клиента A");
    addEvent(eventQueue, "Запрос от клиента B");
    addEvent(eventQueue, "Запрос от клиента C");
    
    processEvents(eventQueue); // Обработает запрос от клиента A
    processEvents(eventQueue); // Обработает запрос от клиента B
    processEvents(eventQueue); // Обработает запрос от клиента C
    processEvents(eventQueue); // Выведет "Очередь событий пуста"
    
    return 0;
}