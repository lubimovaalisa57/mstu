#include <iostream>
#include <string>
using namespace std;

const int MAX_BOOKS = 100;

struct Book 
{
    string title;
    string author;
    int year;
    string genre;
};

struct Library 
{
    Book books[MAX_BOOKS];
    int count = 0;
};

void addBook(Library& lib) 
{
    if (lib.count >= MAX_BOOKS) {
        cout << "Библиотека полна" << endl;
        return;
    }
    
    cout << "Введите название: ";
    cin >> lib.books[lib.count].title;
    cout << "Введите автора: ";
    cin >> lib.books[lib.count].author;
    cout << "Введите год: ";
    cin >> lib.books[lib.count].year;
    cout << "Введите жанр: ";
    cin >> lib.books[lib.count].genre;
    
    lib.count++;
    cout << "Книга добавлена" << endl;
}

void deleteBook(Library& lib) 
{
    string title;
    cout << "Введите название для удаления: ";
    cin >> title;
    
    for (int i = 0; i < lib.count; i++) {
        if (lib.books[i].title == title) {
            for (int j = i; j < lib.count - 1; j++) {
                lib.books[j] = lib.books[j + 1];
            }
            lib.count--;
            cout << "Книга удалена" << endl;
            return;
        }
    }
    cout << "Книга не найдена" << endl;
}

void searchByAuthor(const Library& lib) 
{
    string author;
    cout << "Введите автора: ";
    cin >> author;
    
    bool found = false;
    for (int i = 0; i < lib.count; i++) {
        if (lib.books[i].author == author) {
            cout << lib.books[i].title << " " << lib.books[i].year 
                 << " " << lib.books[i].genre << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Книги не найдены" << endl;
    }
}

void displayAll(const Library& lib) 
{
    if (lib.count == 0) {
        cout << "Библиотека пуста" << endl;
        return;
    }
    
    for (int i = 0; i < lib.count; i++) {
        cout << lib.books[i].title << " " << lib.books[i].author 
             << " " << lib.books[i].year << " " << lib.books[i].genre << endl;
    }
}

int main() 
{
    Library lib;
    int choice;
    
    do {
        cout << "1. Добавить книгу" << endl;
        cout << "2. Удалить книгу" << endl;
        cout << "3. Найти по автору" << endl;
        cout << "4. Показать все" << endl;
        cout << "5. Выход" << endl;
        cout << "Выбор: ";
        cin >> choice;
        
        if (choice == 1) addBook(lib);
        else if (choice == 2) deleteBook(lib);
        else if (choice == 3) searchByAuthor(lib);
        else if (choice == 4) displayAll(lib);
        
    } while (choice != 5);
    
    return 0;
}