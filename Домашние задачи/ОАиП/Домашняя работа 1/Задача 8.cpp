#include <iostream>
#include <string>
using namespace std;

int main() {
    string text;
    int count = 0;
    

    string elements = "euyoaEYUOA";
    
    cout << "Введите строку: ";
    getline(cin, text);
    
    for (char c : text) {
        if (elements.find(c) != string::npos) {
        count++;
        }
    }
    
    cout << "Количество гласных букв: " << count << endl;
    
    return 0;
}