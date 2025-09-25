#include <iostream>

int main()
{
    int n;
    std::cin>>n;

    long sum = 0;
   
    for ( int i=0;i<=n; ) {
        if (i % 2 == 0 || i % 5 ==0) {
            sum +=i;
        }
        i++;
    }
    std::cout << "Сумма чисел от 0 до "<< n <<", которые делятся на 2 или на 5: "<< sum << std::endl;
    return 0;
}