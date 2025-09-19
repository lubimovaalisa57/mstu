#include <iostream>
int main()
{
    int a;
    std::cin>>a;
    int c=a%2;
    if ( c!=0) {
        std::cout<<"Число нечётное"<<std::endl;

    }
    else {
        std::cout<<"Число чётное"<<std::endl;
    }
    return 0;
}