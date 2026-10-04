#pragma once

#include <string>
#include <vector>

namespace makersplace::school {

class FeeAccount {
private:
    std::string studentId;
    double balance = 0;                // amount currently owed
    std::vector<std::string> history;  // one line per transaction

public:
    explicit FeeAccount(std::string id);

    void charge(double amount);  // throws std::invalid_argument if amount <= 0
    void pay(double amount);     // throws std::invalid_argument if amount <= 0 or more than owed

    std::string getStudentId() const { return studentId; }
    double getBalance() const { return balance; }
    const std::vector<std::string>& getHistory() const { return history; }
};

} // namespace makersplace::school
