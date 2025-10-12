#include <iostream>
int main() 
{
    double arr[4][3];
    
    std::cout << "Введите координаты четырех точек:" << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "Точка " << i+1 << " (x y z): ";
        std::cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
    }
    
    double x1 = arr[0][0], y1 = arr[0][1], z1 = arr[0][2];
    double x2 = arr[1][0], y2 = arr[1][1], z2 = arr[1][2];
    double x3 = arr[2][0], y3 = arr[2][1], z3 = arr[2][2];
    double x4 = arr[3][0], y4 = arr[3][1], z4 = arr[3][2];
    
    // Вычисляем суммы квадратов координат
    double s1 = x1*x1 + y1*y1 + z1*z1;
    double s2 = x2*x2 + y2*y2 + z2*z2;
    double s3 = x3*x3 + y3*y3 + z3*z3;
    double s4 = x4*x4 + y4*y4 + z4*z4;
    
    // Вычисляем определитель основной матрицы
    double det = x1*(y2*(z3 - z4) + y3*(z4 - z2) + y4*(z2 - z3))
               - x2*(y1*(z3 - z4) + y3*(z4 - z1) + y4*(z1 - z3))
               + x3*(y1*(z2 - z4) + y2*(z4 - z1) + y4*(z1 - z2))
               - x4*(y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2));
    
    if (det == 0) {
        std::cout << "Точки лежат в одной плоскости" << std::endl;
        return 0;
    }
    
    // Вычисляем определители для коэффициентов A, B, C, D
    double detA = s1*(y2*(z3 - z4) + y3*(z4 - z2) + y4*(z2 - z3))
                - s2*(y1*(z3 - z4) + y3*(z4 - z1) + y4*(z1 - z3))
                + s3*(y1*(z2 - z4) + y2*(z4 - z1) + y4*(z1 - z2))
                - s4*(y1*(z2 - z3) + y2*(z3 - z1) + y3*(z1 - z2));
    
    double detB = x1*(s2*(z3 - z4) + s3*(z4 - z2) + s4*(z2 - z3))
                - x2*(s1*(z3 - z4) + s3*(z4 - z1) + s4*(z1 - z3))
                + x3*(s1*(z2 - z4) + s2*(z4 - z1) + s4*(z1 - z2))
                - x4*(s1*(z2 - z3) + s2*(z3 - z1) + s3*(z1 - z2));
    
    double detC = x1*(y2*(s3 - s4) + y3*(s4 - s2) + y4*(s2 - s3))
                - x2*(y1*(s3 - s4) + y3*(s4 - s1) + y4*(s1 - s3))
                + x3*(y1*(s2 - s4) + y2*(s4 - s1) + y4*(s1 - s2))
                - x4*(y1*(s2 - s3) + y2*(s3 - s1) + y3*(s1 - s2));
    
    double detD = x1*(y2*(z3*s4 - z4*s3) + y3*(z4*s2 - z2*s4) + y4*(z2*s3 - z3*s2))
                - x2*(y1*(z3*s4 - z4*s3) + y3*(z4*s1 - z1*s4) + y4*(z1*s3 - z3*s1))
                + x3*(y1*(z2*s4 - z4*s2) + y2*(z4*s1 - z1*s4) + y4*(z1*s2 - z2*s1))
                - x4*(y1*(z2*s3 - z3*s2) + y2*(z3*s1 - z1*s3) + y3*(z1*s2 - z2*s1));
    
    // Находим коэффициенты уравнения сферы
    double A = detA / det;
    double B = detB / det;
    double C = detC / det;
    double D = (-detD / det);
    
    // Вычисляем центр и радиус сферы
    double x0 = (A / 2);
    double y0 = (B / 2);
    double z0 = (C / 2);
    double r = sqrt(x0*x0 + y0*y0 + z0*z0 - D);

    std::cout << "Уравнение сферы:" << std::endl;
    std::cout << "x² + y² + z² + " << A << "x + " << B << "y + " << C << "z + " << D << " = 0" << std::endl;
    
    if (x0==0, y0==0, z0==0){
        std::cout << "Центр: (" << 0 << ", " << 0 << ", " << 0 << ")" << std::endl;
    }
    else{
        std::cout << "Центр: (" << x0 << ", " << y0 << ", " << z0 << ")" << std::endl;
    }
    
    std::cout << "Радиус: " << r << std::endl;
    
    return 0;
}