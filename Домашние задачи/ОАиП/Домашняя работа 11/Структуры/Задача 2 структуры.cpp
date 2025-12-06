#include <iostream>
#include <vector>
#include <string>

struct BankAccount 
{
    int accountNumber;
    std::string ownerName;
    double balance;
};

int findAccount(const std::vector<BankAccount>& accounts, int accountNumber) 
{
    for (size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1;
}

int main() 
{
    std::vector<BankAccount> accounts;
    int choice;
    
    do {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Создать новый банковский счет" << std::endl;
        std::cout << "2. Пополнить счет" << std::endl;
        std::cout << "3. Снять деньги со счета" << std::endl;
        std::cout << "4. Показать информацию о счете" << std::endl;
        std::cout << "5. Выйти" << std::endl;
        std::cin >> choice;
        
        if (choice == 1) {
            BankAccount newAccount;
            std::cout << "Введите номер счета: ";
            std::cin >> newAccount.accountNumber;
            std::cout << "Введите имя владельца счета: ";
            std::cin >> newAccount.ownerName;
            newAccount.balance = 0;
            accounts.push_back(newAccount);
            std::cout << "Банковский счет создан." << std::endl;
        }
        else if (choice == 2) {
            int accNum;
            double amount;
            std::cout << "Введите номер счета для пополнения: ";
            std::cin >> accNum;
            std::cout << "Введите сумму для пополнения: ";
            std::cin >> amount;
            
            int index = findAccount(accounts, accNum);
            if (index != -1) {
                accounts[index].balance += amount;
                std::cout << "Счет пополнен на " << amount << " рублей." << std::endl;
            } else {
                std::cout << "Счет не найден." << std::endl;
            }
        }
        else if (choice == 3) {
            int accNum;
            double amount;
            std::cout << "Введите номер счета для снятия: ";
            std::cin >> accNum;
            std::cout << "Введите сумму для снятия: ";
            std::cin >> amount;
            
            int index = findAccount(accounts, accNum);
            if (index != -1) {
                if (accounts[index].balance >= amount) {
                    accounts[index].balance -= amount;
                    std::cout << "Со счета снято " << amount << " рублей." << std::endl;
                } else {
                    std::cout << "Недостаточно средств." << std::endl;
                }
            } else {
                std::cout << "Счет не найден." << std::endl;
            }
        }
        else if (choice == 4) {
            int accNum;
            std::cout << "Введите номер счета для показа информации: ";
            std::cin >> accNum;
            
            int index = findAccount(accounts, accNum);
            if (index != -1) {
                std::cout << "Номер счета: " << accounts[index].accountNumber << std::endl;
                std::cout << "Имя владельца счета: " << accounts[index].ownerName << std::endl;
                std::cout << "Баланс: " << accounts[index].balance << " рублей" << std::endl;
            } else {
                std::cout << "Счет не найден." << std::endl;
            }
        }
        
    } while (choice != 5);
    
    std::cout << "Программа завершена." << std::endl;
    return 0;
}