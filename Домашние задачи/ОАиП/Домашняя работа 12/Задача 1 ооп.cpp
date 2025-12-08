#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    int year;
    
public:
    void setInfo(string t, string a, int y) {
        title = t;
        author = a;
        year = y;
    }
    
    void displayInfo() {
        cout << "Название: " << title << ", Автор: " << author << ", Год выпуска: " << year << endl;
    }
};

int main() {
    Book book;
    book.setInfo("Война и мир", "Лев Толстой", 1869);
    book.displayInfo();
    
    return 0;
}