// Exercise 1: Design Patterns - Observer, Strategy and Factory together
//
// Build an automatic SCHOOL BELL system.
//
// TODO 1 (Strategy): Write an abstract class BellSchedule with
//           virtual std::vector<std::string> times() const = 0;
//           virtual std::string name() const = 0;
//         and two strategies:
//           NormalDay - bells at 08:00, 09:30, 10:00, 11:30, 12:30, 14:00
//           ExamDay   - bells at 08:30, 11:30, 12:30, 15:30
// TODO 2 (Observer): Write an interface BellListener with
//           virtual void onBell(const std::string& time) = 0;
//         and three listeners:
//           ClassroomSpeaker - prints "  [speaker <room>] RING at <time>"
//           StaffAlert       - prints "  [staff SMS] bell at <time>"
//           BellLog          - counts the bells it has heard (count() getter)
// TODO 3 (Subject): Write class SchoolBell that holds a const BellSchedule*
//         (setSchedule to swap it at runtime) and a list of BellListener*,
//         with subscribe(), unsubscribe(), and runDay() which notifies
//         every listener at every time in the current schedule.
// TODO 4 (Factory): Write
//           std::unique_ptr<BellListener> makeListener(const std::string& type,
//                                                      const std::string& detail)
//         that creates a "speaker" (detail = room name) or a "staff"
//         listener, and throws std::invalid_argument for anything else.
// TODO 5: In main, build listeners from the configuration lines given, run a
//         normal day, unsubscribe the staff alert, switch to the exam
//         schedule, run again, and print how many bells the log heard.
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// TODO 1-4

int main() {
    // Configuration lines: "type detail"
    std::vector<std::pair<std::string, std::string>> config = {
        {"speaker", "JHS 1"}, {"speaker", "Robotics Lab"}, {"staff", ""}, {"projector", "Hall"}};

    // TODO 5

    (void)config; // remove this line when you use config
    return 0;
}
