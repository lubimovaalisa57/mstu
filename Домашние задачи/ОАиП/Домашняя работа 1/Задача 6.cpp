#include <iostream>
int main()
{
   int a;
   std::cin>>a;
   if (a<18){
    std::cout<<"Меньше 18"<<std::endl;
   } 
   if(a>=18 and a<=60){
    std::cout<<"Больше 18 и меньше 60"<<std::endl;
   }
   if (a>60){
    std::cout<<"Больше 60"<<std::endl;
   }
}