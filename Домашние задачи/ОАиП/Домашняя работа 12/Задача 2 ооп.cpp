#include <iostream>
using namespace std;

class Rectangle {
private:
    double length;
    double width;
    
public:
    void setDimensions(double l, double w) {
        length = l;
        width = w;
    }
    
    double calculateArea() {
        return length * width;
    }
    
    double calculatePerimeter() {
        return 2 * (length + width);
    }
    
    void displayInfo() {
        cout << "Длина: " << length << ", Ширина: " << width 
             << ", Площадь: " << calculateArea() 
             << ", Периметр: " << calculatePerimeter() << endl;
    }
};

int main() {
    Rectangle rect;
    rect.setDimensions(5.0, 3.0);
    rect.displayInfo();
    
    return 0;
}