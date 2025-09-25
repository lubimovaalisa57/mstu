#include <iostream>
 int main()
 {
    int a;
    std::cin>>a;
    while (a!=0){
        int c;
        c=a*a;
        std::cout<< c  <<std::endl;
        a--;
    }
    return 0;
 }