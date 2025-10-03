#include <iostream>

int main()
{ 
     int arr[2][2];
     for (int i = 0; i < 2 ; i++) {
        std::cout << "Вершина " << (i + 1) << " (x y): ";
        std::cin >> arr[i][0] >> arr[i][1];
}
    int x1 = arr[0][0], y1 = arr[0][1];
    int x2 = arr[1][0], y2 = arr[1][1];

    double dx = x2 - x1;
    double dy = y2 - y1;
    double dlina = sqrt(dx * dx + dy * dy);
    
    std::cout << "Длина отрезка: " << dlina << std::endl;
    
    return 0;
}