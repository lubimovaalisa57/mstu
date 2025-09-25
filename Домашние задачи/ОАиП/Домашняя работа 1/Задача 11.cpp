#include <iostream>


int main() {

    
    for (int i = 32; i <= 126; i++) {
        std::cout << "       " << i;           
        std::cout << "       " << char(i);     
        std::cout <<std::endl;
    }
    
    return 0;
}