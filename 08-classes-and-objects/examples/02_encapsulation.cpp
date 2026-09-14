// private hides data from outside code; public methods control access.
#include <iostream>
#include <string>

class BankAccount {
private:
    std::string ownerName;
    double balance = 0.0; // default member initializer - avoids using an uninitialized balance

public:
    void setOwnerName(std::string name) {
        ownerName = name;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    double getBalance() {
        return balance;
    }
};

int main() {
    BankAccount account;
    account.setOwnerName("Ama");
    account.deposit(100.0);

    std::cout << account.getBalance() << std::endl; // 100

    // account.balance = -500;  // <- uncomment: compiler error, balance is private

    return 0;
}
