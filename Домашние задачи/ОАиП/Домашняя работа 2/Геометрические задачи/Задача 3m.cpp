#include <iostream>

int main()
{ 
     int arr[3][2];
     for (int i = 0; i < 3; i++) {
        std::cout << "Вершина " << (i + 1) << " (x y): ";
        std::cin >> arr[i][0] >> arr[i][1];
}
    int x1 = arr[0][0], y1 = arr[0][1];
    int x2 = arr[1][0], y2 = arr[1][1];
    int x3 = arr[2][0], y3 = arr[2][1];

    double summ_x = x1 + x2 + x3;
    double summ_y = y1 + y2 + y3;

    double Cx = summ_x / 3.0;
    double Cy = summ_y / 3.0;

    std::cout << "Центр масс треугольника:" << std::endl;
    std::cout << "Cx = " << Cx << std::endl;
    std::cout << "Cy = " << Cy << std::endl;
    return 0;
}