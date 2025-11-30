#include <iostream>
#include <fstream>

struct Student 
{
    int id;
    char name[50];
    int age;
    double average_grade;
};

int main() 
{
    Student students[] = {
        {1, "Иван Петров", 20, 4.5},
        {2, "Мария Сидорова", 19, 4.8},
        {3, "Алексей Иванов", 21, 4.2}
    };

    // Запись студентов в файл
    std::ofstream out("students.dat", std::ios::binary);
    for (int i = 0; i < 3; i++) {
        out.write(reinterpret_cast<char*>(&students[i]), sizeof(Student));
    }
    out.close();

    // Чтение студентов из файла
    std::ifstream in("students.dat", std::ios::binary);
    in.seekg(0, std::ios::end);
    int file_size = in.tellg();
    in.seekg(0, std::ios::beg);
    
    int count = file_size / sizeof(Student);
    Student* read_students = new Student[count];
    
    for (int i = 0; i < count; i++) {
        in.read(reinterpret_cast<char*>(&read_students[i]), sizeof(Student));
    }
    in.close();

    // Вывод всех студентов
    double max_grade = 0;
    int best_student = 0;
    
    for (int i = 0; i < count; i++) {
        std::cout << read_students[i].id << " " 
                  << read_students[i].name << " " 
                  << read_students[i].age << " " 
                  << read_students[i].average_grade << std::endl;
        
        if (read_students[i].average_grade > max_grade) {
            max_grade = read_students[i].average_grade;
            best_student = i;
        }
    }

    std::cout << "Всего студентов: " << count << std::endl;
    std::cout << "Лучший студент: " << read_students[best_student].name 
              << " с баллом " << max_grade << std::endl;

    delete[] read_students;
    return 0;
}