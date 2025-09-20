#include <iostream>

int main() 
{
    float a;
    std::cin>>a;
    
    if (a>50){
        std::cout<<"Топлива достаточно"<<std::endl;
    }
    if (a<20){
        std::cout<<"Топливо на исходе, срочно заправьтесь"<<std::endl;
    }
    if( a<=50 and a>=20) {
        std::cout<<"Рекомендуется заправиться"<<std::endl;
    }
    
return 0;

}

