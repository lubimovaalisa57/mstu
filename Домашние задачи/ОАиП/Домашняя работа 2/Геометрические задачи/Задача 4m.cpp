#include <iostream>

int main()
{ 
     int arr[4][2];
     for (int i = 0; i < 4; i++) {
        std::cout << "Вершина " << (i + 1) << " (x y): ";
        std::cin >> arr[i][0] >> arr[i][1];
}
    int x1 = arr[0][0], y1 = arr[0][1];
    int x2 = arr[1][0], y2 = arr[1][1];
    int x3 = arr[2][0], y3 = arr[2][1];
    int x4 = arr[3][0], y4 = arr[3][1];
    
    double dx = x3 - x1;
    double dy = y3 - y1;
    double diagonal = sqrt(dx * dx + dy * dy);
    
    std::cout << "Длина диагонали прямоугольника: " << diagonal << std::endl;
    
    return 0;
}