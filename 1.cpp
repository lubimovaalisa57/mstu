#include <iostream>
//using namespace std;
int main()
{
    int a;
    std::cin>>a;
    if (a >50) {
        std::cout << "Топлива достаточно" << std::endl;
    } else if (a < 20) {
        std::cout << "Топливо на исходе, срочно заправьтесь!." << std::endl;
    } else {
        std::cout << "Рекомендуется заправка" << std::endl;
    }
    return 0;
}