#include <iostream>

int main() 
{
    double arr[3][2]; 
    
    std::cout << "Введите координаты трех точек:" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "Точка " << i+1 << " (x y): ";
        std::cin >> arr[i][0] >> arr[i][1];
    }
     double x1 = arr[0][0], y1 = arr[0][1];
    double x2 = arr[1][0], y2 = arr[1][1];
    double x3 = arr[2][0], y3 = arr[2][1];

    
    double det = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    
    std::cout << "Определитель: " << det << std::endl;
    
    if (det == 0) {
        std::cout << "Точки коллинеарны" << std::endl;
    } else {
        std::cout << "Точки не коллинеарны" << std::endl;
    }
    
    return 0;
}