#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Book {
    string title;   
    string author;  
    int year;       
};

// Функция добавления книги
void addBook() {
    ofstream file("books.txt", ios::app);
    ofstream output("output.txt", ios::app); // файл для вывода
    string title;
    
    cout << "Введите название книги (Enter для выхода): ";
    getline(cin, title);
    if(title.empty()) return;
    
    Book book;
    book.title = title;
    
    cout << "Введите автора: ";
    getline(cin, book.author);
    
    cout << "Введите год: ";
    cin >> book.year;
    cin.ignore(); // чистим буфер после ввода числа
    file << book.title << "|" << book.author << "|" << book.year << endl;
    file.close();
    
    // Записываем в output.txt
    output << "Добавлена книга: " << book.title << "|" << book.author << "|" << book.year << endl;
    output.close();
    
    cout << "Книга добавлена!\n";
}

// Функция поиска книги
void searchBook() {
    string search;
    cout << "Введите название для поиска: ";
    getline(cin, search);
    
    // Открываем файл для чтения
    ifstream file("books.txt");
    ofstream output("output.txt", ios::app); // файл для вывода
    string line;
    bool found = false;
    
    while(getline(file, line)) {
        if(line.find(search) != string::npos) {
            cout << "Найдено: " << line << endl;
            output << "Найдено: " << line << endl;
            found = true;
        }
    }
    
    if(!found) {
        cout << "Не найдено\n";
        output << "Не найдено\n";
    }
    file.close();
    output.close();
}

// Функция сортировки книг
void sortBooks() {
    ifstream file("books.txt");
    ofstream output("output.txt", ios::app); // файл для вывода
    vector<Book> books; // вектор для хранения книг
    string line;
    
    // Читаем все книги в вектор
    while(getline(file, line)) {
        Book b;
        // Разбиваем строку на части по разделителю |
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1+1);
        b.title = line.substr(0, p1);
        b.author = line.substr(p1+1, p2-p1-1);
        b.year = stoi(line.substr(p2+1)); // stoi - строка в число
        books.push_back(b);
    }
    file.close();
    
    cout << "Сортировать по (1-автор, 2-год): ";
    int choice;
    cin >> choice;
    cin.ignore();
    
    if(choice == 1) {
        output << "Сортировка по автору:" << endl;
        sort(books.begin(), books.end(), [](Book a, Book b) { return a.author < b.author; });
    } else {
        output << "Сортировка по году:" << endl;
        sort(books.begin(), books.end(), [](Book a, Book b) { return a.year < b.year; });
    }
    
    ofstream f("books.txt");
    for(auto book : books) {
        f << book.title << "|" << book.author << "|" << book.year << endl;
        output << book.title << "|" << book.author << "|" << book.year << endl;
    }
    f.close();
    output.close();
    
    cout << "Файл отсортирован!\n";
}

// Функция поиска старых книг
void findOldBooks() {
    int year;
    cout << "Введите максимальный год: ";
    cin >> year;
    cin.ignore();
    
    ifstream file("books.txt");
    ofstream output("output.txt", ios::app); // файл для вывода
    string line;
    
    output << "Книги до " << year << " года:" << endl;
    
    while(getline(file, line)) {
        size_t p = line.find_last_of('|');
        int bookYear = stoi(line.substr(p+1));
        if(bookYear <= year) {
            cout << line << endl;
            output << line << endl;
        }
    }
    
    file.close();
    output.close();
}

int main() {
    int vibor;
    
    // Бесконечный цикл меню
    do {
        cout << "\n=== МЕНЮ ===" << endl;
        cout << "1. Добавить книгу" << endl;
        cout << "2. Поиск книги" << endl;
        cout << "3. Сортировка книг" << endl;
        cout << "4. Найти старые книги" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите: ";
        cin >> vibor;
        cin.ignore(); // чистим буфер после ввода числа
        
        // Обработка выбора
        switch (vibor) {
            case 1:
                addBook();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                sortBooks();
                break;
            case 4:
                findOldBooks();
                break;
            case 0:
                cout << "Пока!\n";
                break;
            default:
                cout << "Неверный выбор!\n";
        }
    } while (vibor != 0); // пока не ввели 0
    
    return 0;
}