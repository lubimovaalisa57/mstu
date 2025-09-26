#include <iostream>

int main() 
{
    int a;
    std::cin>>a;
    int b = 100;
    int c = a / b;
    int d = a % b;

    std::cout<<"метров "<< c<<" сантиметров "<<d<<std::endl;
return 0;

}