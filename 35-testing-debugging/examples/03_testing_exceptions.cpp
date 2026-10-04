// Testing exceptions, invariants and the strong guarantee (Module 31).
#include "minitest.h"

#include <map>
#include <stdexcept>
#include <string>

class InsufficientFundsError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class Bank {
private:
    std::map<std::string, double> balances;

public:
    void open(const std::string& id, double amount) {
        if (amount < 0) throw std::invalid_argument("negative opening balance");
        balances[id] = amount;
    }
    double balance(const std::string& id) const { return balances.at(id); } // throws std::out_of_range

    // Strong guarantee: all checks happen before anything changes.
    void transfer(const std::string& from, const std::string& to, double amount) {
        if (amount <= 0) throw std::invalid_argument("amount must be positive");
        double& source = balances.at(from);
        double& target = balances.at(to);
        if (amount > source) throw InsufficientFundsError("not enough money in " + from);
        source -= amount;
        target += amount;
    }

    double total() const {
        double t = 0;
        for (const auto& entry : balances) t += entry.second;
        return t;
    }
};

int main() {
    minitest::testCase("a negative opening balance is rejected");
    {
        Bank bank;
        CHECK_THROWS(bank.open("A", -5), std::invalid_argument);
    }

    minitest::testCase("transfer moves money and keeps the total the same (invariant)");
    {
        Bank bank;
        bank.open("A", 100);
        bank.open("B", 50);
        bank.transfer("A", "B", 30);
        CHECK_EQ(bank.balance("A"), 70.0);
        CHECK_EQ(bank.balance("B"), 80.0);
        CHECK_EQ(bank.total(), 150.0);
    }

    minitest::testCase("over-drawing throws InsufficientFundsError and changes NOTHING (strong guarantee)");
    {
        Bank bank;
        bank.open("A", 100);
        bank.open("B", 50);
        CHECK_THROWS(bank.transfer("A", "B", 500), InsufficientFundsError);
        CHECK_EQ(bank.balance("A"), 100.0);
        CHECK_EQ(bank.balance("B"), 50.0);
    }

    minitest::testCase("an unknown account throws std::out_of_range and changes nothing");
    {
        Bank bank;
        bank.open("A", 100);
        CHECK_THROWS(bank.transfer("A", "Z", 10), std::out_of_range);
        CHECK_EQ(bank.balance("A"), 100.0);
    }

    minitest::testCase("zero and negative amounts are rejected");
    {
        Bank bank;
        bank.open("A", 100);
        bank.open("B", 0);
        CHECK_THROWS(bank.transfer("A", "B", 0), std::invalid_argument);
        CHECK_THROWS(bank.transfer("A", "B", -1), std::invalid_argument);
    }

    return TEST_SUMMARY();
}
