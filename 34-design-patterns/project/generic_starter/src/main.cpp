// Module 34 project - Track A: School Events Hub
// Design your classes in include/ and src/, then make this scenario run.
#include "events.h"

#include <iostream>
#include <string>
#include <vector>

int main() {
    // Configuration lines for the FACTORY: "kind,id,name[,extra]"
    std::vector<std::string> config = {
        "student,MP-001,Ama Mensah,JHS 2",   "student,MP-002,Kojo Asante,JHS 2",
        "student,MP-003,Esi Quaye,JHS 3",    "teacher,T-01,Mrs Addo,Science",
        "teacher,T-02,Mr Mensah,Mathematics", "parent,MP-001,0244000001",
    };

    std::cout << "SCENARIO" << std::endl;
    std::cout << "1. Build the school from the config lines (Factory), arranged as" << std::endl;
    std::cout << "   school -> departments -> classes (Composite), and print the headcount" << std::endl;
    std::cout << "   for the school, one department, and one class." << std::endl;
    std::cout << "2. Subscribe a ParentSms, a HeadTeacherDashboard and an AuditLog (Observer)." << std::endl;
    std::cout << "3. Enter three scores with commands; correct one; undo the correction (Command)." << std::endl;
    std::cout << "4. Publish results - every listener reacts." << std::endl;
    std::cout << "5. Print JHS 2's report with letter grades, then WASSCE grades (Strategy)." << std::endl;
    std::cout << "6. Record a fee payment - every listener reacts; unsubscribe the dashboard; pay again." << std::endl;
    std::cout << "7. Build one timetable entry with the Builder." << std::endl;

    (void)config; // TODO: remove when you use the config
    return 0;
}
