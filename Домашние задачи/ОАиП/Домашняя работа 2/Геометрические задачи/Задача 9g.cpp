#include <iostream>

int main()
{
    int n1, n2;
    std::cout << "Количество вершин первого многоугольника: ";
    std::cin >> n1;
    int arr1[n1+1][2];  // +1 для повторения первой вершины
    for (int i = 0; i < n1; i++) {
        std::cout << "Вершина " << (i + 1) << " (x y): ";
        std::cin >> arr1[i][0] >> arr1[i][1];
    }
    // Последняя вершина = первая вершина
    arr1[n1][0] = arr1[0][0];
    arr1[n1][1] = arr1[0][1];
    
    std::cout << "Количество вершин второго многоугольника: ";
    std::cin >> n2;
    int arr2[n2+1][2];  // +1 для повторения первой вершины
    for (int i = 0; i < n2; i++) {
        std::cout << "Вершина " << (i + 1) << " (x y): ";
        std::cin >> arr2[i][0] >> arr2[i][1];
    }
    // Последняя вершина = первая вершина
    arr2[n2][0] = arr2[0][0];
    arr2[n2][1] = arr2[0][1];
    
    bool peresechenie = false;
    
    for (int i = 0; i < n1; i++) {
        int x1 = arr1[i][0], y1 = arr1[i][1];
        int x2 = arr1[i+1][0], y2 = arr1[i+1][1];  
        
        for (int j = 0; j < n2; j++) {
            int x3 = arr2[j][0], y3 = arr2[j][1];
            int x4 = arr2[j+1][0], y4 = arr2[j+1][1];  
            
            int v1 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
            int v2 = (x4 - x3) * (y2 - y3) - (y4 - y3) * (x2 - x3);
            int v3 = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
            int v4 = (x2 - x1) * (y4 - y1) - (y2 - y1) * (x4 - x1);
            
            if ((v1 * v2 <= 0) && (v3 * v4 <= 0)) {
                peresechenie = true;
                break;
            }
        }
        
    }
    
    if (peresechenie == true) {
        std::cout << "Многоугольники пересекаются" << std::endl;
    }
    else {
        std::cout << "Многоугольники не пересекаются" << std::endl;
    }
    
    return 0;
}