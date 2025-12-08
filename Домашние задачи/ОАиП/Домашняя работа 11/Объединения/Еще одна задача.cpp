#include <iostream>
#include <string>
#include <vector>
using namespace std;

union StudentInfo {
    struct {
        int recordBookNumber;
        int age;
        double averageScore;
        char fullName[100];
    };
    char rawData[112];
};

void addStudent(vector<StudentInfo>& students) {
    StudentInfo s;
    cout << "Введите ФИО: ";
    cin.ignore();
    cin.getline(s.fullName, 100);
    cout << "Введите возраст: ";
    cin >> s.age;
    cout << "Введите средний балл: ";
    cin >> s.averageScore;
    cout << "Введите номер зачетки: ";
    cin >> s.recordBookNumber;
    students.push_back(s);
}

void displayAll(const vector<StudentInfo>& students) {
    for (const auto& s : students) {
        cout << s.fullName << " " << s.age << " " 
             << s.averageScore << " " << s.recordBookNumber << endl;
    }
}

void findByRecordBook(const vector<StudentInfo>& students, int number) {
    for (const auto& s : students) {
        if (s.recordBookNumber == number) {
            cout << s.fullName << " " << s.age << " " 
                 << s.averageScore << " " << s.recordBookNumber << endl;
            return;
        }
    }
    cout << "Не найден" << endl;
}

void displayAboveScore(const vector<StudentInfo>& students, double score) {
    for (const auto& s : students) {
        if (s.averageScore > score) {
            cout << s.fullName << " " << s.averageScore << endl;
        }
    }
}

int main() {
    vector<StudentInfo> students;
    int choice;
    
    do {
        cout << "1. Добавить студента" << endl;
        cout << "2. Показать всех" << endl;
        cout << "3. Найти по номеру зачетки" << endl;
        cout << "4. Показать с баллом выше" << endl;
        cout << "5. Выход" << endl;
        cout << "Выбор: ";
        cin >> choice;
        
        if (choice == 1) addStudent(students);
        else if (choice == 2) displayAll(students);
        else if (choice == 3) {
            int num;
            cout << "Введите номер зачетки: ";
            cin >> num;
            findByRecordBook(students, num);
        }
        else if (choice == 4) {
            double score;
            cout << "Введите минимальный балл: ";
            cin >> score;
            displayAboveScore(students, score);
        }
    } while (choice != 5);
    
    return 0;
}