#include <iostream>

int main() 
{
    double arr[3][2]; 
    for (int i = 0; i < 3; i++) {
        std::cout << "Введите координаты " << (i+1) << "-й точки (x y): ";
        std::cin >> arr[i][0] >> arr[i][1];
    }
    
    double x1 = arr[0][0], y1 = arr[0][1];
    double x2 = arr[1][0], y2 = arr[1][1];
    double x3 = arr[2][0], y3 = arr[2][1];

    int matrix[3][3];
    std::cout << "Введите координаты точек в матрицу:" << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cin >> matrix[i][j];
        }
    }
    
    double det = x1 * (y2 - y3) - y1 * (x2 - x3) + (x2 * y3 - x3 * y2);
    
    double ploshad = 0.5 * det;
    
    std::cout << "Площадь треугольника: " << ploshad << std::endl;
    
    return 0;
} 