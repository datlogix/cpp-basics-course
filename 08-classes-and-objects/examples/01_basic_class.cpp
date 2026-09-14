// A class bundles data (member variables) and behavior (methods).
#include <iostream>
#include <string>

class BankAccount {
public:
    std::string ownerName;
    double balance;

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            std::cout << "Insufficient funds!" << std::endl;
        }
    }

    void printStatement() {
        std::cout << ownerName << "'s balance: " << balance << std::endl;
    }
};

int main() {
    BankAccount account;
    account.ownerName = "Ama";
    account.balance = 100.0;

    account.deposit(50.0);
    account.withdraw(30.0);
    account.printStatement(); // Ama's balance: 120

    return 0;
}
