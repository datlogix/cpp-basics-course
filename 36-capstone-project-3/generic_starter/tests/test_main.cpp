// Capstone 3 test suite (Stage 4): at least 40 checks.
// Group tests by class; use fakes for every interface that talks to the
// outside world (files, clocks, notifications).
#include "money.h"
#include "errors.h"
#include "minitest.h"
#include "repository.h"
#include "statistics.h"

using namespace makersplace::school;

int main() {
    minitest::testCase("Money adds in pesewas without rounding errors");
    {
        Money a = Money::fromCedis(0.10);
        Money b = Money::fromCedis(0.20);
        CHECK_EQ((a + b).inPesewas(), 30L);
    }

    minitest::testCase("Statistics mean of a few values");
    {
        Statistics<int> s;
        s.add(2);
        s.add(4);
        CHECK_EQ(s.mean(), 3.0);
    }

    minitest::testCase("CorruptRecordError reports file and line");
    {
        CorruptRecordError e("data.csv", 7, "bad number");
        CHECK_EQ(e.getLine(), 7);
        CHECK(std::string(e.what()).find("line 7") != std::string::npos);
    }

    // TODO (Stage 4): many more tests.

    return TEST_SUMMARY();
}
