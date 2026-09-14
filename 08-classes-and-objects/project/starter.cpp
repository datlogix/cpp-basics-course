// Module 8 Project: Bank Account Simulator
// See project/README.md for requirements.
#include <iostream>
#include <string>
#include <vector>

class BankAccount {
private:
    std::string ownerName;
    double balance;
    std::vector<std::string> transactionHistory;

public:
    BankAccount(std::string name, double startingBalance) {
        // TODO: set ownerName, balance, and record the opening transaction.
    }

    void deposit(double amount) {
        // TODO
    }

    void withdraw(double amount) {
        // TODO
    }

    double getBalance() {
        // TODO
        return 0;
    }

    void printHistory() {
        // TODO
    }
};

int main() {
    BankAccount account("Douglas", 100.0);

    int choice;
    do {
        std::cout << std::endl;
        std::cout << "1. Deposit" << std::endl;
        std::cout << "2. Withdraw" << std::endl;
        std::cout << "3. Check balance" << std::endl;
        std::cout << "4. Print history" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                // TODO: read an amount, call account.deposit(amount)
                break;
            case 2:
                // TODO: read an amount, call account.withdraw(amount)
                break;
            case 3:
                // TODO: print account.getBalance()
                break;
            case 4:
                account.printHistory();
                break;
            case 5:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option." << std::endl;
        }
    } while (choice != 5);

    return 0;
}
