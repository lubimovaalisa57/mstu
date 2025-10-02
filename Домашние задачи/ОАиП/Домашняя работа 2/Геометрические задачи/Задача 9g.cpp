#include <iostream>

int main()
{ 
    int n;
    std::cin >> n;
    int arr1[n][2];

        for (int i = 0; i < n; i++) {
            std::cout << "Вершина " << (i + 1) << " (x y): ";
            std::cin >> arr1[i][0] >> arr1[i][1];
        }


    int m;
    std::cin >> m;
    int arr2[m][2];
    
        for (int i = 0; i < m; i++) {
            std::cout << "Вершина " << (i + 1) << " (x y): ";
            std::cin >> arr2[i][0] >> arr2[i][1];
        }

// Функция для вычисления ориентации трех точек
// Возвращает:
// 0 - точки коллинеарны
// 1 - по часовой стрелке
// 2 - против часовой стрелки
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    
        if (fabs(val) < 1e-9) return 0; // коллинеарны
        return (val > 0) ? 1 : 2; // по часовой или против
    }

// Функция проверки, лежит ли точка q на отрезке pr
    bool onSegment(Point p, Point q, Point r) {
        if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) {
            return true;
        }
        return false;
    }

// Функция проверки пересечения двух отрезков (p1q1 и p2q2)
    bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
        // Находим ориентации для всех комбинаций
        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);
    
    // Общий случай
        if (o1 != o2 && o3 != o4) {
            return true;
        }
    
    // Особые случаи (коллинеарность)
    // p1, q1 и p2 коллинеарны и p2 лежит на отрезке p1q1
        if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    
    // p1, q1 и q2 коллинеарны и q2 лежит на отрезке p1q1
        if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    
    // p2, q2 и p1 коллинеарны и p1 лежит на отрезке p2q2
        if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    
    // p2, q2 и q1 коллинеарны и q1 лежит на отрезке p2q2
        if (o4 == 0 && onSegment(p2, q1, q2)) return true;
    
        return false;
    }

// Функция проверки пересечения двух многоугольников
    bool polygonsIntersect(const vector<Point>& poly1, const vector<Point>& poly2) {
        int n1 = poly1.size();
        int n2 = poly2.size();
    
    // Проверяем пересечение каждой стороны первого многоугольника
    // с каждой стороной второго многоугольника
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                Point p1 = poly1[i];
                Point q1 = poly1[(i + 1) % n1]; // следующая вершина (замыкаем многоугольник)
                Point p2 = poly2[j];
                Point q2 = poly2[(j + 1) % n2]; // следующая вершина
            
                if (doIntersect(p1, q1, p2, q2)) {
                    return true;
                }
            }
        }
    
        return false;
    }

// Функция для ввода вершин многоугольника
    vector<Point> inputPolygon(const string& name) {
        int n;
        cout << "Введите количество вершин многоугольника " << name << ": ";
        cin >> n;
    
        vector<Point> polygon;
        cout << "Введите координаты вершин (x y) для многоугольника " << name << ":\n";
        for (int i = 0; i < n; i++) {
            double x, y;
            cout << "Вершина " << (i + 1) << ": ";
            cin >> x >> y;
            polygon.push_back(Point(x, y));
        }
    
        return polygon;
    }

// Функция для вывода многоугольника
    void printPolygon(const vector<Point>& polygon, const string& name) {
        cout << "Многоугольник " << name << ":\n";
        for (size_t i = 0; i < polygon.size(); i++) {
            cout << "(" << polygon[i].x << ", " << polygon[i].y << ")";
            if (i < polygon.size() - 1) cout << " -> ";
        }
        cout << endl;
    }

    int main() {
        cout << "=== ПРОВЕРКА ПЕРЕСЕЧЕНИЯ ДВУХ МНОГОУГОЛЬНИКОВ ===\n\n";
    
    // Ввод первого многоугольника
        vector<Point> polygon1 = inputPolygon("A");
        cout << endl;
    
    // Ввод второго многоугольника
        vector<Point> polygon2 = inputPolygon("B");
        cout << endl;
    
    // Вывод введенных многоугольников
        printPolygon(polygon1, "A");
        printPolygon(polygon2, "B");
        cout << endl;
    
    // Проверка пересечения
        bool intersect = polygonsIntersect(polygon1, polygon2);
    
    // Вывод результата
        if (intersect) {
            cout << "Результат: Многоугольники ПЕРЕСЕКАЮТСЯ";
        } 
        else {
            cout << "Результат: Многоугольники НЕ ПЕРЕСЕКАЮТСЯ";
        }
    
        return 0;
    }
}