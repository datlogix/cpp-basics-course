#pragma once

#include "fee_account.h"

#include <string>
#include <vector>

namespace makersplace::school {

class Notifier {
public:
    virtual ~Notifier() = default;
    virtual void send(const std::string& studentId, const std::string& message) = 0;
};

class FeeReminder {
private:
    Notifier& notifier;
    double threshold;

public:
    FeeReminder(Notifier& n, double thresholdGhs);
    int remind(const std::vector<FeeAccount>& accounts); // returns how many reminders were sent
};

} // namespace makersplace::school
