#include "attendance_session.h"

#include <iostream>

namespace makersplace::school {

AttendanceSession::AttendanceSession(std::string clubName, std::string meetingDate)
    : log("attendance_log.txt", std::ios::app), club(clubName), date(meetingDate) {
    // TODO: print a "[+] ..." trace line and write "OPEN <club> <date>" to the log
}

AttendanceSession::~AttendanceSession() {
    // TODO: write "CLOSE <club> <date> - <n> present" to the log and print a
    // "[-] ..." trace line
}

void AttendanceSession::markPresent(const Student& s) {
    // TODO: increase presentCount, write the student's ID and name to the log
    (void)s;
}

} // namespace makersplace::school
