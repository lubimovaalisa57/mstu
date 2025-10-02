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

    int length_1 = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    int length_2 = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    int length_3 = sqrt((x4 - x3) * (x4 - x3) + (y4 - y3) * (y4 - y3));
    int length_4 = sqrt((x1 - x4) * (x1 - x4) + (y1 - y4) * (y1 - y4));

   
    int P = length_1 + length_2 + length_3 + length_4;
    
    
    
    std::cout << "Периметр четырехугольника: " << P << std::
    endl;
    
    return 0;
}
