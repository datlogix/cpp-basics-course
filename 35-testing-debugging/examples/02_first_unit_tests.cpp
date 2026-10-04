// First unit tests with minitest.h, in Arrange-Act-Assert form.
// Build with sanitizers on, as a habit:
//   g++ -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined 02_first_unit_tests.cpp -o tests
//   ./tests
#include "minitest.h"

#include <stdexcept>
#include <string>

// ---------- the class under test ----------
class BankAccount {
private:
    std::string owner;
    double balance;

public:
    BankAccount(std::string o, double opening) : owner(o), balance(opening) {
        if (owner.empty()) throw std::invalid_argument("owner required");
        if (opening < 0) throw std::invalid_argument("opening balance cannot be negative");
    }
    double getBalance() const { return balance; }
    void deposit(double amount) {
        if (amount <= 0) throw std::invalid_argument("deposit must be positive");
        balance += amount;
    }
    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        return true;
    }
};

// ---------- the tests ----------
int main() {
    minitest::testCase("a new account holds its opening balance");
    {
        BankAccount account("Ama", 100); // Arrange
        // (nothing to Act on)
        CHECK_EQ(account.getBalance(), 100.0); // Assert
    }

    minitest::testCase("depositing increases the balance");
    {
        BankAccount account("Ama", 100);
        account.deposit(50);
        CHECK_EQ(account.getBalance(), 150.0);
    }

    minitest::testCase("withdrawing reduces the balance");
    {
        BankAccount account("Ama", 100);
        bool ok = account.withdraw(30);
        CHECK(ok);
        CHECK_EQ(account.getBalance(), 70.0);
    }

    minitest::testCase("withdrawing exactly the whole balance is allowed (boundary)");
    {
        BankAccount account("Ama", 100);
        CHECK(account.withdraw(100));
        CHECK_EQ(account.getBalance(), 0.0);
    }

    minitest::testCase("withdrawing more than the balance is refused and changes nothing");
    {
        BankAccount account("Ama", 100);
        CHECK(!account.withdraw(100.01));
        CHECK_EQ(account.getBalance(), 100.0);
    }

    minitest::testCase("this check is WRONG on purpose, to show a failure message");
    {
        BankAccount account("Ama", 100);
        account.deposit(10);
        CHECK_EQ(account.getBalance(), 100.0); // should be 110 - watch the FAIL line
    }

    return TEST_SUMMARY();
}
