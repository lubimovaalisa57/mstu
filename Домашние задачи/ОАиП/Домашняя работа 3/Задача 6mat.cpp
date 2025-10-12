#include <iostream>

int main() 
{
    double matrix[2][3] = {
        {2, 3, 13},
        {5, -1, 9}
    };
    
    std::cout << "Система уравнений:" << std::endl;
    std::cout << "2x + 3y = 13" << std::endl;
    std::cout << "5x - y = 9" << std::endl;
    std::cout << std::endl;
    
    // Вычисляем определитель основной матрицы
    double det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    std::cout << "Определитель основной матрицы: " << det << std::endl;
    
    if (det == 0) {
        std::cout << "Система не имеет единственного решения" << std::endl;
        return 0;
    }
    
    // Вычисляем определитель для x 
    double det_x = matrix[0][2] * matrix[1][1] - matrix[0][1] * matrix[1][2];
    
    // Вычисляем определитель для y 
    double det_y = matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0];
    
    double x = det_x / det;
    double y = det_y / det;
    
    std::cout << "Решение:" << std::endl;
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    
    // Проверка решения
    std::cout << "Проверка:" << std::endl;
    double check1 = 2*x + 3*y;
    double check2 = 5*x - y;
    std::cout << "2*" << x << " + 3*" << y << " = " << check1 << " (должно быть 13)" << std::endl;
    std::cout << "5*" << x << " - " << y << " = " << check2 << " (должно быть 9)" << std::endl;
    
    return 0;
}