#include "fee_reminder.h"

namespace makersplace::school {

FeeReminder::FeeReminder(Notifier& n, double thresholdGhs) : notifier(n), threshold(thresholdGhs) {}

int FeeReminder::remind(const std::vector<FeeAccount>& accounts) {
    int sent = 0;
    for (const FeeAccount& a : accounts) {
        if (a.getBalance() > threshold) {
            notifier.send(a.getStudentId(), "Fees outstanding: GHS " + std::to_string(a.getBalance()));
            sent++;
        }
    }
    return sent;
}

} // namespace makersplace::school
