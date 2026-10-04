// Tests for DoseCalculator and PrescriptionChecker. Aim for at least 25 checks.
// Remember: one behaviour per testCase, Arrange-Act-Assert.
#include "dose_calculator.h"
#include "minitest.h"
#include "prescription_checker.h"

#include <stdexcept>

using namespace makersplace::clinic;

// TODO: a FakePager that records every page it is asked to send.

int main() {
    minitest::testCase("dose is weight times mg/kg below the cap");
    {
        DoseCalculator calc(15, 1000);
        CHECK_EQ(calc.doseMg(10), 150.0);
    }

    // TODO: many more tests...

    return TEST_SUMMARY();
}
