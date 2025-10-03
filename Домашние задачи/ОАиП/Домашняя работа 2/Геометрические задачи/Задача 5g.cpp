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

    double vekt_proisv = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);

    if (vekt_proisv == 0) {
        std::cout << "Точки лежат на одной прямой" << std::endl;
    }
    else{
        std:: cout << "Точки не лежат на одной прямой" << std:: endl;
    }
    return 0;
}

