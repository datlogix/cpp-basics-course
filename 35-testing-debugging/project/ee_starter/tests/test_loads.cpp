// Tests for Circuit and LoadMonitor. Aim for at least 25 checks.
// Remember: one behaviour per testCase, Arrange-Act-Assert.
#include "load_monitor.h"
#include "minitest.h"

#include <stdexcept>

using namespace makersplace::energy;

// TODO: a FakeAlarm that records every circuit it is asked to raise.

int main() {
    minitest::testCase("a new circuit has no loads");
    {
        Circuit c("Lounge", 10);
        CHECK_EQ(c.loadCount(), 0);
    }

    // TODO: many more tests...

    return TEST_SUMMARY();
}
