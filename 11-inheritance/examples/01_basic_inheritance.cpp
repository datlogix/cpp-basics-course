// A derived class automatically gets everything the base class has,
// and can add its own members on top.
#include <iostream>
#include <string>

class BankAccount {
protected:
    std::string ownerName;
    double balance;

public:
    BankAccount(std::string name, double startingBalance) {
        ownerName = name;
        balance = startingBalance;
    }

    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    double getBalance() {
        return balance;
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(std::string name, double startingBalance, double rate)
        : BankAccount(name, startingBalance) {
        interestRate = rate;
    }

    void applyInterest() {
        balance += balance * interestRate; // uses the inherited protected member
    }
};

int main() {
    SavingsAccount acc("Ama", 1000.0, 0.05);
    acc.deposit(200.0);       // inherited, unchanged
    acc.applyInterest();      // new, only SavingsAccount has this
    std::cout << "Balance: " << acc.getBalance() << std::endl;

    return 0;
}
