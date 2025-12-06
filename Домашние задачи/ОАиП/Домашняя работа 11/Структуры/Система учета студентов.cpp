#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Student 
{
    std::string fullName;
    int age;
    double averageScore;
    int recordBookNumber;
};

class StudentDatabase 
{
private:
    std::vector<Student> students;

public:
    void addStudent(const Student& newStudent) {
        students.push_back(newStudent);
    }

    void displayAllStudents() const 
    {
        if (students.empty()) {
            std::cout << "Список студентов пуст." << std::endl;
            return;
        }
        
        for (const auto& student : students) {
            std::cout << "ФИО: " << student.fullName 
                      << ", Возраст: " << student.age 
                      << ", Средний балл: " << student.averageScore 
                      << ", Номер зачетки: " << student.recordBookNumber 
                      << std::endl;
        }
    }

    void findStudentByRecordBook(int recordNumber) const 
    {
        for (const auto& student : students) {
            if (student.recordBookNumber == recordNumber) {
                std::cout << "Найден студент: " << student.fullName 
                          << ", Возраст: " << student.age 
                          << ", Средний балл: " << student.averageScore 
                          << ", Номер зачетки: " << student.recordBookNumber 
                          << std::endl;
                return;
            }
        }
        std::cout << "Студент с номером зачетки " << recordNumber << " не найден." << std::endl;
    }

    void displayStudentsAboveScore(double minScore) const 
    {
        bool found = false;
        for (const auto& student : students) {
            if (student.averageScore > minScore) {
                std::cout << "ФИО: " << student.fullName 
                          << ", Средний балл: " << student.averageScore 
                          << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "Нет студентов с баллом выше " << minScore << std::endl;
        }
    }
};

int main() 
{
    StudentDatabase database;
    
    // Добавление тестовых данных
    database.addStudent({"Иванов Иван Иванович", 20, 4.5, 1001});
    database.addStudent({"Петров Петр Петрович", 21, 3.8, 1002});
    database.addStudent({"Сидорова Мария Сергеевна", 19, 4.9, 1003});
    database.addStudent({"Кузнецов Алексей Владимирович", 22, 3.2, 1004});
    
    // Тестирование функций
    std::cout << "Все студенты:" << std::endl;
    database.displayAllStudents();
    
    std::cout << "\nПоиск студента с номером зачетки 1003:" << std::endl;
    database.findStudentByRecordBook(1003);
    
    std::cout << "\nПоиск студента с номером зачетки 9999:" << std::endl;
    database.findStudentByRecordBook(9999);
    
    std::cout << "\nСтуденты с баллом выше 4.0:" << std::endl;
    database.displayStudentsAboveScore(4.0);
    
    return 0;
}