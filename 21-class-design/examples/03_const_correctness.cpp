// const member functions can be called on const objects and through
// const references. Non-const ones can't.
#include <iostream>
#include <string>

class BankAccount {
private:
    std::string owner;
    double balance = 0;

public:
    explicit BankAccount(std::string name) : owner(name) {}

    // These only READ, so they are const.
    double getBalance() const { return balance; }
    std::string getOwner() const { return owner; }

    // This CHANGES the object, so it is not const.
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    // Uncomment to see the compiler enforce the const promise:
    // void broken() const { balance = 0; } // ERROR: modifies a member in a const method
};

// Takes a const reference: no copy, and a promise not to change the account.
void printStatement(const BankAccount& account) {
    std::cout << account.getOwner() << ": GHS " << account.getBalance() << std::endl;
    // account.deposit(10); // ERROR: deposit() is not const
}

int main() {
    BankAccount account("Efua");
    account.deposit(250.0);
    printStatement(account);

    const BankAccount frozen("Archived account");
    std::cout << "Frozen balance: " << frozen.getBalance() << std::endl; // OK
    // frozen.deposit(5); // ERROR: can't call a non-const method on a const object

    return 0;
}
