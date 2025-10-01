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

    int length = sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));


    
    // Вычисляем периметр
    int P = 0;
    
    // Складываем расстояния между последовательными вершинами
    for (int i = 0; i < 4; i++) {
        int j = (i + 1) % 4; // следующая вершина (для связи последней с первой)
        double side = distance(vertices[i], vertices[j]);
        perimeter += side;
        
        // Выводим длину каждой стороны (опционально)
        cout << "Сторона " << (i + 1) << "-" << (j + 1) << ": " << side << endl;
    }
    
    cout << fixed << setprecision(2);
    cout << "Периметр четырехугольника: " << perimeter << endl;
    
    return 0;
}
}