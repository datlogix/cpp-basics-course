#include "staff.h"

#include <iostream>

namespace makersplace::school {

StaffMember::StaffMember(std::string n) : name(n) {}

StaffMember::~StaffMember() {
    std::cout << "  [-] staff " << name << std::endl;
}

Teacher::Teacher(std::string n, double base, int subjects)
    : StaffMember(n), baseSalary(base), subjectsTaught(subjects) {}

std::string Teacher::role() const { return "Teacher"; }

double Teacher::monthlySalaryGhs() const {
    // TODO: baseSalary + 150 * subjectsTaught
    return 0;
}

Administrator::Administrator(std::string n, double salary) : StaffMember(n), fixedSalary(salary) {}

std::string Administrator::role() const { return "Administrator"; }

double Administrator::monthlySalaryGhs() const { return fixedSalary; }

} // namespace makersplace::school
