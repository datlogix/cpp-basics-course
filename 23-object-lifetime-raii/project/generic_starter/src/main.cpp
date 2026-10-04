// TODO (README requirement 5): Why must the AttendanceSession be an
// automatic (stack) object, not one created with new?
//
#include "attendance_session.h"
#include "student.h"

#include <iostream>
#include <string>
#include <vector>

using makersplace::school::AttendanceSession;
using makersplace::school::Student;

// Each event is either a student's name, or the special text "FIRE DRILL".
void runMeeting(std::string club, std::string date, const std::vector<std::string>& events) {
    std::cout << "Meeting of " << club << " on " << date << std::endl;
    // TODO: create an AttendanceSession, then go through events:
    //   - "FIRE DRILL" -> print a message and RETURN EARLY
    //   - an empty name -> print "invalid student" and RETURN EARLY
    //   - otherwise create a Student and markPresent() them
    // Finally print how many were present.
    (void)events;
}

int main() {
    runMeeting("Robotics Club", "2026-10-03", {"Ama", "Kojo", "Esi"});
    runMeeting("Coding Club", "2026-10-04", {"Yaw", "FIRE DRILL", "Akua"});
    runMeeting("Robotics Club", "2026-10-10", {"Ama", "", "Kojo"});
    return 0;
}
