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
    
    int vekt1 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
    int vekt2 = (x4 - x3) * (y2 - y3) - (y4 - y3) * (x2 - x3);
    int vekt3 = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    int vekt4 = (x2 - x1) * (y4 - y1) - (y2 - y1) * (x4 - x1);
    
    if ((vekt1 * vekt2 <= 0) && (vekt3 * vekt4 <= 0)) {
        std::cout << "Отрезки пересекаются" << std::endl;
    }
    else {
        std::cout << "Отрезки не пересекаются" << std::endl;
    }
    
    return 0;
}