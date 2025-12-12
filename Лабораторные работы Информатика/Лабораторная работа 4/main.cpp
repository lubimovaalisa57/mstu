#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <functional>

// ========== КЛАССЫ ==========
class Author {
public:
    int id = 0;
    std::string name;
    int birthYear = 0;
    Author(const std::string& n = "", int y = 0) : name(n), birthYear(y) {}
};

class Book {
public:
    int id = 0, authorId = 0, publicationYear = 0;
    std::string title, genre;
    Book(const std::string& t = "", int a = 0, int y = 0, const std::string& g = "")
        : title(t), authorId(a), publicationYear(y), genre(g) {}
    virtual ~Book() = default;
    virtual std::string type() const { return "Book"; }
};

class FictionBook : public Book {
public:
    ~FictionBook() override = default;
    std::string type() const override { return "Fiction"; }
};

class NonFictionBook : public Book {
public:
    ~NonFictionBook() override = default;
    std::string type() const override { return "Non-Fiction"; }
};

class User {
public:
    int id = 0;
    std::string name, regDate;
    User(const std::string& n = "", const std::string& d = "") : name(n), regDate(d) {}
};

class Borrowed {
public:
    int userId = 0, bookId = 0;
    std::string borrowDate, returnDate;
    Borrowed(int u = 0, int b = 0, const std::string& d = "")
        : userId(u), bookId(b), borrowDate(d) {}
};

template<typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;
    Pair(const T1& f = T1(), const T2& s = T2()) : first(f), second(s) {}
};

// ========== БАЗА ДАННЫХ ==========
class Database {
    pqxx::connection* conn = nullptr;
    std::string connStr;

    bool transact(const std::function<void(pqxx::work&)>& f) {
        if (!conn || !conn->is_open()) return false;
        try {
            pqxx::work txn(*conn);
            f(txn);
            txn.commit();
            log("Success", "Transaction completed");
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            log("Error", e.what());
            return false;
        }
    }

    static void log(const std::string& op, const std::string& det) {
        std::ofstream f("log.txt", std::ios::app);
        auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        f << std::put_time(std::localtime(&t), "%F %T") << " | " << op << " | " << det << "\n";
        f.close();
    }

public:
    Database(const std::string& cs) : connStr(cs) {}

    bool connect() {
        try {
            conn = new pqxx::connection(connStr);
            if (conn->is_open()) {
                log("DB", "Connected");
                return true;
            }
        } catch (...) {}
        return false;
    }

    void setup() {
        transact([](pqxx::work& t) {
            t.exec("CREATE TABLE IF NOT EXISTS authors(id SERIAL PRIMARY KEY, name TEXT, birth_year INT)");
            t.exec("CREATE TABLE IF NOT EXISTS books(id SERIAL PRIMARY KEY, title TEXT, author_id INT, publication_year INT, genre TEXT)");
            t.exec("CREATE TABLE IF NOT EXISTS users(id SERIAL PRIMARY KEY, name TEXT, registration_date DATE DEFAULT CURRENT_DATE)");
            t.exec("CREATE TABLE IF NOT EXISTS borrowed_books(user_id INT, book_id INT, borrow_date DATE DEFAULT CURRENT_DATE, return_date DATE)");
            t.exec("CREATE INDEX IF NOT EXISTS idx_authors_name ON authors(name)");
            t.exec("CREATE INDEX IF NOT EXISTS idx_books_title ON books(title)");
            t.exec("CREATE INDEX IF NOT EXISTS idx_borrowed_books_date ON borrowed_books(borrow_date)");
        });
    }

    bool addAuthor(Author& a) {
        return transact([&](pqxx::work& t) {
            auto r = t.exec("INSERT INTO authors(name, birth_year) VALUES(" +
                           t.quote(a.name) + "," + t.quote(a.birthYear) + ") RETURNING id");
            if (!r.empty()) a.id = r[0][0].as<int>();
        });
    }

    bool addBook(Book& b) {
        return transact([&](pqxx::work& t) {
            auto r = t.exec("INSERT INTO books(title, author_id, publication_year, genre) VALUES(" +
                           t.quote(b.title) + "," + t.quote(b.authorId) + "," +
                           t.quote(b.publicationYear) + "," + t.quote(b.genre) + ") RETURNING id");
            if (!r.empty()) b.id = r[0][0].as<int>();
        });
    }

    bool addUser(User& u) {
        return transact([&](pqxx::work& t) {
            auto r = t.exec("INSERT INTO users(name) VALUES(" + t.quote(u.name) + ") RETURNING id, registration_date");
            if (!r.empty()) { u.id = r[0][0].as<int>(); u.regDate = r[0][1].c_str(); }
        });
    }

    bool borrowBook(const Borrowed& bb) {
        return transact([&](pqxx::work& t) {
            if (bb.borrowDate.empty()) {
                // Если дата не указана, используем текущую дату
                t.exec("INSERT INTO borrowed_books(user_id, book_id, borrow_date) VALUES(" +
                       t.quote(bb.userId) + "," + t.quote(bb.bookId) + ", CURRENT_DATE)");
            } else {
                t.exec("INSERT INTO borrowed_books(user_id, book_id, borrow_date) VALUES(" +
                       t.quote(bb.userId) + "," + t.quote(bb.bookId) + "," +
                       t.quote(bb.borrowDate) + ")");
            }
        });
    }

    void booksByAuthor(int aid) const {
        if (!conn || !conn->is_open()) return;
        try {
            pqxx::work t(*conn);
            auto r = t.exec("SELECT title, publication_year FROM books WHERE author_id=" + t.quote(aid));
            std::cout << "Книги автора:\n";
            for (const auto& row : r) std::cout << "- " << row[0].c_str() << " (" << row[1].as<int>() << ")\n";
        } catch (...) {}
    }

    int usersLastYear() const {
        if (!conn || !conn->is_open()) return 0;
        try {
            pqxx::work t(*conn);
            auto r = t.exec("SELECT COUNT(*) FROM users WHERE registration_date >= CURRENT_DATE - INTERVAL '1 year'");
            return r[0][0].as<int>();
        } catch (...) { return 0; }
    }

    void booksLast30Days() const {
        if (!conn || !conn->is_open()) return;
        try {
            pqxx::work t(*conn);
            auto r = t.exec("SELECT b.title FROM books b JOIN borrowed_books bb ON b.id=bb.book_id WHERE bb.borrow_date >= CURRENT_DATE - INTERVAL '30 days'");
            std::cout << "Книги за 30 дней:\n";
            for (const auto& row : r) std::cout << "- " << row[0].c_str() << "\n";
        } catch (...) {}
    }

    void top3Books() const {
        if (!conn || !conn->is_open()) return;
        try {
            pqxx::work t(*conn);
            auto r = t.exec("SELECT b.title, COUNT(*) as cnt FROM books b JOIN borrowed_books bb ON b.id=bb.book_id GROUP BY b.title ORDER BY cnt DESC LIMIT 3");
            std::cout << "Топ-3 книги:\n";
            for (const auto& row : r) std::cout << "- " << row[0].c_str() << " (" << row[1].as<int>() << " займов)\n";
        } catch (...) {}
    }

    // Метод для возврата книги
    bool returnBook(int userId, int bookId) {
        return transact([&](pqxx::work& t) {
            t.exec("UPDATE borrowed_books SET return_date = CURRENT_DATE WHERE user_id = " +
                   t.quote(userId) + " AND book_id = " + t.quote(bookId) + " AND return_date IS NULL");
        });
    }

    ~Database() {
        if (conn && conn->is_open()) conn->close();
        delete conn;
    }
};

// ========== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ==========
std::string currentDate() {
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&t));
    return buf;
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

Author inputAuthor() {
    Author a;
    std::cout << "Имя автора: "; clearInput(); std::getline(std::cin, a.name);
    std::cout << "Год рождения: "; std::cin >> a.birthYear;
    return a;
}

Book inputBook() {
    Book b;
    std::cout << "Название: "; clearInput(); std::getline(std::cin, b.title);
    std::cout << "ID автора: "; std::cin >> b.authorId;
    std::cout << "Год публикации: "; std::cin >> b.publicationYear;
    std::cout << "Жанр: "; clearInput(); std::getline(std::cin, b.genre);
    return b;
}

User inputUser() {
    User u;
    std::cout << "Имя: "; clearInput(); std::getline(std::cin, u.name);
    u.regDate = currentDate();
    return u;
}

Borrowed inputBorrow() {
    Borrowed bb;
    std::cout << "ID пользователя: "; std::cin >> bb.userId;
    std::cout << "ID книги: "; std::cin >> bb.bookId;
    bb.borrowDate = currentDate();
    return bb;
}

Borrowed inputReturn() {
    Borrowed bb;
    std::cout << "ID пользователя: "; std::cin >> bb.userId;
    std::cout << "ID книги: "; std::cin >> bb.bookId;
    bb.returnDate = currentDate();
    return bb;
}

void showMenu() {
    std::cout << "\n=== БИБЛИОТЕКА ===\n"
              << "1. Добавить автора\n2. Добавить книгу\n3. Добавить пользователя\n"
              << "4. Заём книги\n5. Вернуть книгу\n6. Книги автора\n"
              << "7. Пользователи за год\n8. Книги за 30 дней\n"
              << "9. Топ-3 книги\n10. Художественная книга\n"
              << "11. Научная книга\n0. Выход\nВыбор: ";
}

// ========== ГЛАВНАЯ ФУНКЦИЯ ==========
int main() {
    Database db("dbname=library user=postgres password=your_password host=localhost");

    if (!db.connect()) {
        std::cout << "Ошибка подключения!\n";
        return 1;
    }

    db.setup();
    std::cout << "База данных готова!\n";

    int choice;
    do {
        showMenu();
        std::cin >> choice;

        switch(choice) {
            case 1: {
                Author a = inputAuthor();
                if (db.addAuthor(a)) {
                    std::cout << "Успешно! ID автора: " << a.id << "\n";
                } else {
                    std::cout << "Ошибка!\n";
                }
                break;
            }
            case 2: {
                Book b = inputBook();
                if (db.addBook(b)) {
                    std::cout << "Успешно! ID книги: " << b.id << "\n";
                } else {
                    std::cout << "Ошибка!\n";
                }
                break;
            }
            case 3: {
                User u = inputUser();
                if (db.addUser(u)) {
                    std::cout << "Успешно! ID пользователя: " << u.id << "\n";
                } else {
                    std::cout << "Ошибка!\n";
                }
                break;
            }
            case 4: {
                Borrowed bb = inputBorrow();
                if (db.borrowBook(bb)) {
                    std::cout << "Успешно! Книга выдана.\n";
                } else {
                    std::cout << "Ошибка!\n";
                }
                break;
            }
            case 5: {
                int userId, bookId;
                std::cout << "ID пользователя: "; std::cin >> userId;
                std::cout << "ID книги: "; std::cin >> bookId;
                if (db.returnBook(userId, bookId)) {
                    std::cout << "Успешно! Книга возвращена.\n";
                } else {
                    std::cout << "Ошибка!\n";
                }
                break;
            }
            case 6: {
                int id; std::cout << "ID автора: "; std::cin >> id;
                db.booksByAuthor(id);
                break;
            }
            case 7:
                std::cout << "Пользователей за год: " << db.usersLastYear() << "\n";
                break;
            case 8:
                db.booksLast30Days();
                break;
            case 9:
                db.top3Books();
                break;
            case 10: {
                FictionBook fb;
                std::cout << "Название: "; clearInput(); std::getline(std::cin, fb.title);
                std::cout << "ID автора: "; std::cin >> fb.authorId;
                std::cout << "Год публикации: "; std::cin >> fb.publicationYear;
                std::cout << "Жанр: "; clearInput(); std::getline(std::cin, fb.genre);
                if (db.addBook(fb)) {
                    std::cout << "Художественная книга добавлена! ID: " << fb.id << "\n";
                } else {
                    std::cout << "Ошибка!\n";
                }
                break;
            }
            case 11: {
                NonFictionBook nfb;
                std::cout << "Название: "; clearInput(); std::getline(std::cin, nfb.title);
                std::cout << "ID автора: "; std::cin >> nfb.authorId;
                std::cout << "Год публикации: "; std::cin >> nfb.publicationYear;
                std::cout << "Жанр: "; clearInput(); std::getline(std::cin, nfb.genre);
                if (db.addBook(nfb)) {
                    std::cout << "Научная книга добавлена! ID: " << nfb.id << "\n";
                } else {
                    std::cout << "Ошибка!\n";
                }
                break;
            }
            case 0:
                std::cout << "Выход...\n";
                break;
            default:
                std::cout << "Неверный выбор!\n";
        }

        if (choice != 0) {
            std::cout << "\nНажмите Enter..."; clearInput(); std::cin.get();
        }

    } while (choice != 0);

    return 0;
}