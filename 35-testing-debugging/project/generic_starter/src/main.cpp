#include "fee_reminder.h"

#include <iostream>

using namespace makersplace::school;

class ConsoleNotifier : public Notifier {
public:
    void send(const std::string& studentId, const std::string& message) override {
        std::cout << "  [to parent of " << studentId << "] " << message << std::endl;
    }
};

int main() {
    std::vector<FeeAccount> accounts = {FeeAccount("MP-001"), FeeAccount("MP-002")};
    accounts[0].charge(1500);
    accounts[0].pay(1000);
    accounts[1].charge(1500);

    ConsoleNotifier console;
    FeeReminder reminder(console, 200);
    std::cout << reminder.remind(accounts) << " reminders sent" << std::endl;
    return 0;
}
