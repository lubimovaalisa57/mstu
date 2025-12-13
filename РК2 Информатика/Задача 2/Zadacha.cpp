#include <iostream>
#include <string>

using namespace std;

class BankAccount {
protected:
    string accountNumber;
    string ownerName;
    double balance;

public:
    // Конструктор
    BankAccount(string accNum, string name, double initialBalance)
        : accountNumber(accNum), ownerName(name), balance(initialBalance) {}

    // Метод для пополнения счета
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Пополнение на " << amount << " руб. Успешно!\n";
        } else {
            cout << "Неверная сумма для пополнения!\n";
        }
    }

    // Метод для снятия средств
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Снятие " << amount << " руб. Успешно!\n";
        } else {
            cout << "Недостаточно средств или неверная сумма!\n";
        }
    }

    // Метод для вывода информации
    void displayInfo() {
        cout << "Счет: " << accountNumber << "\n";
        cout << "Владелец: " << ownerName << "\n";
        cout << "Баланс: " << balance << " руб.\n";
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate; // Процентная ставка

public:
    // Конструктор
    SavingsAccount(string accNum, string name, double initialBalance, double rate)
        : BankAccount(accNum, name, initialBalance), interestRate(rate) {}

    // Метод для начисления процентов
    void addInterest() {
        double interest = balance * interestRate / 100;
        balance += interest;
        cout << "Начислены проценты: " << interest << " руб.\n";
    }

    // Метод для вывода информации с учетом процентной ставки
    void displayInfo() {
        BankAccount::displayInfo();
        cout << "Процентная ставка: " << interestRate << "%\n";
    }
};

int main() {
    cout << "=== Банковская система ===\n\n";

    // Создание обычного банковского счета
    BankAccount regularAccount("123456789", "Иван Иванов", 5000.0);
    cout << "Обычный банковский счет:\n";
    regularAccount.displayInfo();
    
    regularAccount.deposit(2000.0);
    regularAccount.withdraw(1000.0);
    regularAccount.withdraw(10000.0); // Попытка снять больше, чем есть
    
    cout << "\n---\n\n";

    // Создание сберегательного счета
    SavingsAccount savingsAccount("987654321", "Мария Петрова", 10000.0, 5.0);
    cout << "Сберегательный счет:\n";
    savingsAccount.displayInfo();
    
    savingsAccount.deposit(3000.0);
    savingsAccount.withdraw(2000.0);
    savingsAccount.addInterest(); // Начисление процентов
    
    cout << "\nИтоговое состояние счетов:\n";
    cout << "1. Обычный счет: ";
    regularAccount.displayInfo();
    cout << "\n2. Сберегательный счет: ";
    savingsAccount.displayInfo();

    return 0;
}