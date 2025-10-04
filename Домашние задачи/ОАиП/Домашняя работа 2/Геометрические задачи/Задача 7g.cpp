#include <iostream>

int main()
{
    int n;
    std::cout << "Количество вершин многоугольника: ";
    std::cin >> n;
    
    int arr[ n + 1 ][ 2 ];  // +1 для повторения первой вершины
    for (int i = 0; i < n; i++) {
        std::cout << "Вершина " << (i + 1) << " (x y): ";
        std::cin >> arr[i][0] >> arr[i][1];
    }
    // Последняя вершина = первая вершина
    arr[n][0] = arr[0][0];
    arr[n][1] = arr[0][1];
    
    int x, y;
    std::cout << "Координаты точки (x y): ";
    std::cin >> x >> y;
    
    bool inside = false;
    
    for (int i = 0; i < n; i++) {
        int x1 = arr[i][0], y1 = arr[i][1];
        int x2 = arr[i+1][0], y2 = arr[i+1][1];
        
        // Проверяем, лежит ли точка между y-координатами ребра
        if ((y1 > y) != (y2 > y)) {
            // Вычисляем x-координату пересечения луча с ребром
            int x_intersect = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
            
            // Если точка справа от пересечения, меняем состояние
            if (x < x_intersect) {
                inside = !inside;
            }
        }
    }
    
    if (inside == true) {
        std::cout << "Точка внутри многоугольника" << std::endl;
    }
    else {
        std::cout << "Точка снаружи многоугольника" << std::endl;
    }
    
    return 0;
}