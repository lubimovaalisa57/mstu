#include <iostream>
 int main()
 {
    int a;
    std::cin>>a;
    if (a>0){
        std::cout<<"Число Положительное"<<std::endl;
    }
    if (a<0){
        std::cout<<"Число Отрицательное"<<std::endl;
    }
    if (a==0){
        std::cout<<"Число равно нулю"<<std::endl;
    }
 }