#include "fee_account.h"

#include <stdexcept>

namespace makersplace::school {

FeeAccount::FeeAccount(std::string id) : studentId(id) {
    if (studentId.empty()) {
        throw std::invalid_argument("student ID required");
    }
}

void FeeAccount::charge(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("charge must be positive");
    }
    balance += amount;
    history.push_back("charge " + std::to_string(amount));
}

void FeeAccount::pay(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("payment must be positive");
    }
    if (amount >= balance) {
        throw std::invalid_argument("payment exceeds the amount owed");
    }
    balance -= amount;
    history.push_back("payment " + std::to_string(amount));
}

} // namespace makersplace::school
