// Tests for FeeAccount and FeeReminder. Aim for at least 25 checks.
// Remember: one behaviour per testCase, Arrange-Act-Assert.
#include "fee_reminder.h"
#include "minitest.h"

#include <stdexcept>

using namespace makersplace::school;

// TODO: a FakeNotifier that records every message it is asked to send.

int main() {
    minitest::testCase("a new account owes nothing");
    {
        FeeAccount account("MP-001");
        CHECK_EQ(account.getBalance(), 0.0);
    }

    // TODO: many more tests...

    return TEST_SUMMARY();
}
