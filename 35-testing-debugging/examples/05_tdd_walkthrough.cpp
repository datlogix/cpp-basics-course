// The END RESULT of a short test-driven development session building a
// TimeSlot class for a school timetable. The comments record each
// RED -> GREEN -> REFACTOR cycle in the order it happened.
#include "minitest.h"

#include <stdexcept>
#include <string>

class TimeSlot {
private:
    int startMinutes; // minutes since midnight
    int endMinutes;

    static int toMinutes(int hour, int minute) { return hour * 60 + minute; }

public:
    // Cycle 1 RED:   test "a slot knows its length in minutes" - didn't compile (no class).
    // Cycle 1 GREEN: wrote the constructor and lengthMinutes().
    // Cycle 3 RED:   test "a slot that ends before it starts is rejected" - failed.
    // Cycle 3 GREEN: added the check below.
    TimeSlot(int startHour, int startMinute, int endHour, int endMinute)
        : startMinutes(toMinutes(startHour, startMinute)), endMinutes(toMinutes(endHour, endMinute)) {
        if (endMinutes <= startMinutes) {
            throw std::invalid_argument("a time slot must end after it starts");
        }
    }

    int lengthMinutes() const { return endMinutes - startMinutes; }

    // Cycle 2 RED:   test "overlapping slots clash" - failed (no method).
    // Cycle 2 GREEN: first version was  return startMinutes == other.startMinutes;  (simplest thing!)
    // Cycle 4 RED:   test "a slot starting inside another clashes" - failed with that version.
    // Cycle 4 GREEN: the real overlap rule below.
    // Cycle 5 RED:   test "back-to-back slots do NOT clash" - passed already (a good sign).
    // Cycle 5 REFACTOR: renamed overlaps() to clashesWith(), which reads better in tests.
    bool clashesWith(const TimeSlot& other) const {
        return startMinutes < other.endMinutes && other.startMinutes < endMinutes;
    }
};

int main() {
    minitest::testCase("a slot knows its length in minutes"); // cycle 1
    CHECK_EQ(TimeSlot(8, 0, 9, 30).lengthMinutes(), 90);

    minitest::testCase("identical slots clash"); // cycle 2
    CHECK(TimeSlot(8, 0, 9, 0).clashesWith(TimeSlot(8, 0, 9, 0)));

    minitest::testCase("a slot that ends before it starts is rejected"); // cycle 3
    CHECK_THROWS(TimeSlot(10, 0, 9, 0), std::invalid_argument);
    CHECK_THROWS(TimeSlot(10, 0, 10, 0), std::invalid_argument);

    minitest::testCase("a slot starting inside another clashes"); // cycle 4
    CHECK(TimeSlot(8, 0, 9, 0).clashesWith(TimeSlot(8, 30, 9, 30)));
    CHECK(TimeSlot(8, 30, 9, 30).clashesWith(TimeSlot(8, 0, 9, 0)));

    minitest::testCase("back-to-back slots do not clash"); // cycle 5
    CHECK(!TimeSlot(8, 0, 9, 0).clashesWith(TimeSlot(9, 0, 10, 0)));

    return TEST_SUMMARY();
}
