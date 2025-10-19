#include <iostream>

int main() 
{
    char A[100];
    char B[100];
    std::cout << "Введите строку A: ";
    std::cin.getline(A, 100);
    std::cout << "Введите строку B: ";
    std::cin.getline(B, 100);
    
    int lengthA = std::strlen(A);
    int lengthB = std::strlen(B);
    
    bool all_found = true;
    
    for (int i = 0; i < lengthB; ++i) {
        bool found = false;
        
        for (int j = 0; j < lengthA; ++j) {
            if (B[i] == A[j]) {
                found = true;
                break;
            }
        }
        
        if (found == false) {
            all_found = false;
            break;
        }
    }
    
    if (all_found == true) {
        std::cout << "Да" << std::endl;
    } else {
        std::cout << "Нет" << std::endl;
    }
    
    return 0;
}