// Dependency Inversion Principle + dependency injection.
// BEFORE: the high-level reminder service is welded to one SMS provider.
// AFTER:  it depends on an abstraction, and the sender is passed in -
//         so we can swap providers, or use a fake one for testing.
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace before {

class BulkSmsGateway { // a low-level detail
public:
    void sendSms(const std::string& phone, const std::string& text) {
        std::cout << "  [SMS to " << phone << "] " << text << std::endl;
    }
};

class FeeReminderService {
private:
    BulkSmsGateway sms; // created INSIDE - can't be replaced or faked

public:
    void remind(const std::map<std::string, double>& balances) {
        for (const auto& entry : balances) {
            if (entry.second > 0) {
                sms.sendSms(entry.first, "Fees outstanding: GHS " + std::to_string(static_cast<int>(entry.second)));
            }
        }
    }
};

} // namespace before

namespace after {

class MessageSender { // the ABSTRACTION, owned by the high-level code
public:
    virtual ~MessageSender() = default;
    virtual void send(const std::string& to, const std::string& text) = 0;
};

class SmsSender : public MessageSender { // a detail, depending on the abstraction
public:
    void send(const std::string& to, const std::string& text) override {
        std::cout << "  [SMS to " << to << "] " << text << std::endl;
    }
};

class EmailSender : public MessageSender {
public:
    void send(const std::string& to, const std::string& text) override {
        std::cout << "  [email to " << to << "] " << text << std::endl;
    }
};

class FakeSender : public MessageSender { // for testing: records instead of sending
public:
    std::vector<std::string> sent;
    void send(const std::string& to, const std::string& text) override { sent.push_back(to + ": " + text); }
};

class FeeReminderService {
private:
    MessageSender& sender; // depends ONLY on the abstraction

public:
    explicit FeeReminderService(MessageSender& s) : sender(s) {} // dependency INJECTION

    int remind(const std::map<std::string, double>& balances) {
        int count = 0;
        for (const auto& entry : balances) {
            if (entry.second > 0) {
                sender.send(entry.first, "Fees outstanding: GHS " + std::to_string(static_cast<int>(entry.second)));
                count++;
            }
        }
        return count;
    }
};

} // namespace after

int main() {
    std::map<std::string, double> balances = {{"0244000001", 350}, {"0244000002", 0}, {"0244000003", 1200}};

    std::cout << "before:" << std::endl;
    before::FeeReminderService oldService;
    oldService.remind(balances);

    std::cout << "after, with SMS:" << std::endl;
    after::SmsSender sms;
    after::FeeReminderService smsService(sms);
    smsService.remind(balances);

    std::cout << "after, with email (no change to FeeReminderService):" << std::endl;
    after::EmailSender email;
    after::FeeReminderService emailService(email);
    emailService.remind(balances);

    std::cout << "after, with a fake sender - checking the logic without sending anything:" << std::endl;
    after::FakeSender fake;
    after::FeeReminderService testService(fake);
    int reminders = testService.remind(balances);
    std::cout << "  " << reminders << " reminders, " << fake.sent.size() << " recorded"
              << (reminders == 2 ? "  -> correct: only debtors were reminded" : "  -> WRONG") << std::endl;
    return 0;
}
