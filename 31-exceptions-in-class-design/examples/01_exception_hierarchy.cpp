// Our own exception hierarchy, rooted at std::runtime_error, including
// an exception that carries DATA. Callers catch at the level they need.
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

class BankError : public std::runtime_error { // the root of OUR hierarchy
public:
    using std::runtime_error::runtime_error;
};

class AccountNotFoundError : public BankError {
public:
    using BankError::BankError;
};

class InsufficientFundsError : public BankError {
private:
    double requested;
    double available;

    static std::string makeMessage(double req, double avail) {
        std::ostringstream out;
        out << "insufficient funds: requested GHS " << req << ", available GHS " << avail;
        return out.str();
    }

public:
    InsufficientFundsError(double req, double avail)
        : BankError(makeMessage(req, avail)), requested(req), available(avail) {}

    double shortfall() const { return requested - available; }
};

class MobileMoneyWallet {
private:
    std::map<std::string, double> balances; // phone number -> balance

public:
    void open(std::string phone, double initial) { balances[phone] = initial; }

    void withdraw(std::string phone, double amount) {
        auto it = balances.find(phone);
        if (it == balances.end()) {
            throw AccountNotFoundError("no wallet for " + phone);
        }
        if (amount <= 0) {
            throw std::invalid_argument("withdrawal amount must be positive"); // a standard one
        }
        if (amount > it->second) {
            throw InsufficientFundsError(amount, it->second);
        }
        it->second -= amount;
    }
};

void attempt(MobileMoneyWallet& w, std::string phone, double amount) {
    try {
        w.withdraw(phone, amount);
        std::cout << "  withdrew GHS " << amount << " from " << phone << std::endl;
    } catch (const InsufficientFundsError& e) { // most specific first: use its DATA
        std::cout << "  " << e.what() << " -> top up GHS " << e.shortfall() << std::endl;
    } catch (const BankError& e) {              // anything else from OUR system
        std::cout << "  bank error: " << e.what() << std::endl;
    } catch (const std::exception& e) {         // anything at all
        std::cout << "  general error: " << e.what() << std::endl;
    }
}

int main() {
    MobileMoneyWallet momo;
    momo.open("0244123456", 200);

    attempt(momo, "0244123456", 50);
    attempt(momo, "0244123456", 500);
    attempt(momo, "0209999999", 10);
    attempt(momo, "0244123456", -5);
    return 0;
}
