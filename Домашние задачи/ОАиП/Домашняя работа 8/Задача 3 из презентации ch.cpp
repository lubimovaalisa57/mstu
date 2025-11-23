#include <iostream>
#include <chrono>

int main() 
{
    long long total_seconds;
    std::cout << "Введите количество секунд: ";
    std::cin >> total_seconds;
    
    using namespace std::chrono;
    
    seconds total(total_seconds);
    hours h = duration_cast<hours>(total);
    minutes m = duration_cast<minutes>(total - h);
    seconds s = total - h - m;
    
    std::cout << h.count() << " часов " 
              << m.count() << " минут " 
              << s.count() << " секунд" << std::endl;
    
    return 0;
}