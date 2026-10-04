// Two versions of the same class. The first has a getter/setter for
// everything and protects nothing. The second offers OPERATIONS that
// keep its invariant ("balance is never negative") true at all times.
#include <iostream>

class LeakyAccount {
private:
    double balance = 0;
public:
    double getBalance() const { return balance; }
    void setBalance(double b) { balance = b; } // private in name only
};

class SafeAccount {
private:
    double balance = 0; // INVARIANT: never negative

public:
    double getBalance() const { return balance; }

    bool deposit(double amount) {
        if (amount <= 0) {
            return false;
        }
        balance += amount;
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) {
            return false; // refusing keeps the invariant true
        }
        balance -= amount;
        return true;
    }
};

int main() {
    LeakyAccount leaky;
    leaky.setBalance(-5000); // nothing stops this
    std::cout << "Leaky balance: " << leaky.getBalance() << std::endl;

    SafeAccount safe;
    safe.deposit(100);
    if (!safe.withdraw(500)) {
        std::cout << "Withdrawal of 500 refused" << std::endl;
    }
    if (!safe.deposit(-20)) {
        std::cout << "Negative deposit refused" << std::endl;
    }
    std::cout << "Safe balance: " << safe.getBalance() << std::endl;
    return 0;
}
