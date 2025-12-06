#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Order 
{
    std::string customerName;
    std::vector<std::string> items;
};

void addOrder(std::queue<Order>& orderQueue, const Order& newOrder) 
{
    orderQueue.push(newOrder);
}

void processOrder(std::queue<Order>& orderQueue) 
{
    if (orderQueue.empty()) {
        std::cout << "Очередь заказов пуста" << std::endl;
    } else {
        Order currentOrder = orderQueue.front();
        std::cout << "Обрабатывается заказ клиента: " << currentOrder.customerName << std::endl;
        std::cout << "Товары: ";
        for (size_t i = 0; i < currentOrder.items.size(); ++i) {
            std::cout << currentOrder.items[i];
            if (i != currentOrder.items.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
        orderQueue.pop();
    }
}

int main() 
{
    std::queue<Order> orderQueue;
    
    // Создание тестовых заказов
    Order order1 = {"Иван Иванов", {"Ноутбук", "Мышка", "Сумка"}};
    Order order2 = {"Мария Петрова", {"Смартфон", "Чехол"}};
    Order order3 = {"Петр Сидоров", {"Наушники"}};
    
    // Тестирование функций
    addOrder(orderQueue, order1);
    addOrder(orderQueue, order2);
    addOrder(orderQueue, order3);
    
    processOrder(orderQueue); // Обработает заказ Ивана
    processOrder(orderQueue); // Обработает заказ Марии
    processOrder(orderQueue); // Обработает заказ Петра
    processOrder(orderQueue); // Выведет "Очередь заказов пуста"
    
    return 0;
}