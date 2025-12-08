#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    int year;
    
public:
    Book(string t, string a, int y) {
        title = t;
        author = a;
        year = y;
    }
    
    void displayInfo() {
        cout << "Название: " << title << ", Автор: " << author << ", Год выпуска: " << year << endl;
    }
};

int main() {
    Book book("Война и мир", "Лев Толстой", 1869);
    book.displayInfo();
    
    return 0;
}