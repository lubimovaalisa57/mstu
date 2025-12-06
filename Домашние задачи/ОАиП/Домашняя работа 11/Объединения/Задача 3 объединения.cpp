#include <iostream>
using namespace std;

union DateTime 
{
    struct {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
    } components;
    
    int allValues[6];
};

int main() 
{
    DateTime dt;
    
    cout << "Введите год: ";
    cin >> dt.components.year;
    cout << "Введите месяц: ";
    cin >> dt.components.month;
    cout << "Введите день: ";
    cin >> dt.components.day;
    cout << "Введите час: ";
    cin >> dt.components.hour;
    cout << "Введите минуту: ";
    cin >> dt.components.minute;
    cout << "Введите секунду: ";
    cin >> dt.components.second;
    
    cout << "Дата и время: " 
         << dt.components.year << "-" 
         << dt.components.month << "-" 
         << dt.components.day << " "
         << dt.components.hour << ":" 
         << dt.components.minute << ":" 
         << dt.components.second << endl;
    
    return 0;
}