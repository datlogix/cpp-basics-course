// A constructor runs automatically when an object is created.
#include <iostream>
#include <string>

class BankAccount {
private:
    std::string ownerName;
    double balance;

public:
    // Parameterized constructor
    BankAccount(std::string name, double startingBalance) {
        ownerName = name;
        balance = startingBalance;
    }

    // Default constructor - needed because we defined the one above
    BankAccount() {
        ownerName = "Unknown";
        balance = 0.0;
    }

    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    double getBalance() {
        return balance;
    }

    std::string getOwnerName() {
        return ownerName;
    }
};

int main() {
    BankAccount kofisAccount("Kofi", 200.0);
    kofisAccount.deposit(50.0);
    std::cout << kofisAccount.getOwnerName() << ": " << kofisAccount.getBalance() << std::endl; // 250

    BankAccount emptyAccount; // uses the default constructor
    std::cout << emptyAccount.getOwnerName() << ": " << emptyAccount.getBalance() << std::endl; // Unknown: 0

    return 0;
}
