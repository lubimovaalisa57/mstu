#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() 
{
    std::vector<int> speeds(50);
    std::cout << "Введите 50 значений скорости автомобиля (от 0 до 180):" << std::endl;
    for (int i = 0; i < 50; ++i) {
        std::cout << "Скорость " << i + 1 << ": ";
        std::cin >> speeds[i];
    }
    
    // Отфильтруем все превышения скорости > 120
    std::vector<int> overspeeds;
    for (int speed : speeds) {
        if (speed > 120) {
            overspeeds.push_back(speed);
        }
    }
    
    // Находим среднюю скорость
    int sum = 0;
    for (int speed : speeds) {
        sum += speed;
    }
    double average_speed = static_cast<double>(sum) / speeds.size();
    
    // Определяем, были ли все значения больше 0
    bool always_moving = true;
    for (int speed : speeds) {
        if (speed <= 0) {
            always_moving = false;
            break;
        }
    }
    
    // Находим 10 максимальных значений скорости
    std::vector<int> sorted_speeds = speeds;
    
    // Сортируем по убыванию
    for (int i = 0; i < sorted_speeds.size() - 1; ++i) {
        for (int j = i + 1; j < sorted_speeds.size(); ++j) {
            if (sorted_speeds[i] < sorted_speeds[j]) {
                int temp = sorted_speeds[i];
                sorted_speeds[i] = sorted_speeds[j];
                sorted_speeds[j] = temp;
            }
        }
    }
    
    // Берем первые 10 элементов
    std::vector<int> top_10_speeds;
    int count = std::min(10, static_cast<int>(sorted_speeds.size()));
    for (int i = 0; i < count; ++i) {
        top_10_speeds.push_back(sorted_speeds[i]);
    }

    std::cout << "Превышения скорости (>120 км/ч): ";
    if (overspeeds.empty()) {
        std::cout << "нет превышений";
    } else {
        for (size_t i = 0; i < overspeeds.size(); ++i) {
            std::cout << overspeeds[i];
            if (i < overspeeds.size() - 1) std::cout << ", ";
        }
    }
    std::cout << std::endl;
    
    std::cout << "Количество превышений: " << overspeeds.size() << std::endl;
    std::cout << "Средняя скорость: " << average_speed << " км/ч" << std::endl;
    
    if (always_moving == true) {
        std::cout << "Автомобиль всегда двигался" << std::endl;
    } 
    else {
        std::cout << "Автомобиль иногда останавливался" << std::endl;
    }
    
    std::cout << "10 максимальных скоростей: ";
    for (size_t i = 0; i < top_10_speeds.size(); ++i) {
        std::cout << top_10_speeds[i];
        if (i < top_10_speeds.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    return 0;
}