#include <iostream>
int main()
{
    int a;
    std::cin>>a;
    int c = a % 3;
    int d = a % 5;
    if (c!=0 and d!=0 or a==0){
        std::cout<<"Число не делится на 3 и на 5"<<std::endl;
    }
    if (c!=0 and d==0){
        std::cout<<"Число делится на 5 и не делится на 3"<<std::endl;
    }
    if (c==0 and d!=0){
        std::cout<<"Число делится на 3 и не делится на 5"<<std::endl;
    }
    if (c==0 and d==0 and a!=0) {
        std::cout<<"Число делится на 3 и на 5"<<std::endl;
    
    }
    

    return 0;
}