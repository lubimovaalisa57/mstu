#include <iostream>
#include <vector>
#include <string>

struct Employee 
{
    std::string name;
    int age;
    std::string position;
    double salary;
};

int main() 
{
    int n;
    std::cout << "Введите количество сотрудников: ";
    std::cin >> n;
    
    std::vector<Employee> employees(n);
    
    for (int i = 0; i < n; i++) {
        std::cout << "Введите имя сотрудника: ";
        std::cin >> employees[i].name;
        std::cout << "Введите возраст сотрудника: ";
        std::cin >> employees[i].age;
        std::cout << "Введите должность сотрудника: ";
        std::cin >> employees[i].position;
        std::cout << "Введите зарплату сотрудника: ";
        std::cin >> employees[i].salary;
    }
    
    Employee youngest = employees[0];
    Employee oldest = employees[0];
    double totalSalary = 0;
    
    for (const auto& emp : employees) {
        if (emp.age < youngest.age) youngest = emp;
        if (emp.age > oldest.age) oldest = emp;
        totalSalary += emp.salary;
    }
    
    std::cout << "Самый молодой сотрудник: " << youngest.name 
              << ", возраст: " << youngest.age 
              << ", должность: " << youngest.position 
              << ", зарплата: " << youngest.salary << std::endl;
    
    std::cout << "Самый старший сотрудник: " << oldest.name 
              << ", возраст: " << oldest.age 
              << ", должность: " << oldest.position 
              << ", зарплата: " << oldest.salary << std::endl;
    
    std::cout << "Средняя зарплата всех сотрудников: " << totalSalary / n << std::endl;
    
    return 0;
}