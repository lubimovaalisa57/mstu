#include <iostream>

int main() 
{
    double x, y, theta_degrees;
    
    std::cout << "Введите координаты точки (x y): ";
    std::cin >> x >> y;
    
    std::cout << "Введите угол поворота в градусах (по часовой стрелке): ";
    std::cin >> theta_degrees;
    
    double theta_radians = theta_degrees * M_PI / 180.0;
    
    double cos_theta = cos(theta_radians);
    double sin_theta = sin(theta_radians);
   
    double x_new = x * cos_theta + y * sin_theta;
    double y_new = -x * sin_theta + y * cos_theta;

    std::cout << "Исходная точка: (" << x << ", " << y << ")" << std::endl;
    std::cout << "Угол поворота: " << theta_degrees  << std::endl;
    std::cout << "Новая точка: (" << x_new << ", " << y_new << ")" << std::endl;
    
    return 0;
}