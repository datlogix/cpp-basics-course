#pragma once

#include "student.h"

#include <fstream>
#include <string>

namespace makersplace::school {

// RAII: constructing an AttendanceSession OPENS a meeting in the log;
// destroying it CLOSES the meeting - on every exit path.
class AttendanceSession {
private:
    std::ofstream log;
    std::string club;
    std::string date;
    int presentCount = 0;

public:
    AttendanceSession(std::string clubName, std::string meetingDate);
    ~AttendanceSession();

    void markPresent(const Student& s);
    int getPresentCount() const { return presentCount; }
};

} // namespace makersplace::school
