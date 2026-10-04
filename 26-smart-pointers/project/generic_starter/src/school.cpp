#include "school.h"

#include <iostream>
#include <utility>

namespace makersplace::school {

School::School(std::string n) : name(n) {}

void School::hire(std::unique_ptr<StaffMember> person) {
    std::cout << "  " << name << " hires " << person->getName() << std::endl;
    staff.push_back(std::move(person));
}

std::unique_ptr<StaffMember> School::release(std::string staffName) {
    // TODO: find the staff member, std::move them out of the vector,
    // erase the empty slot, and return them. Return nullptr if not found.
    (void)staffName;
    return nullptr;
}

void School::printPayroll() const {
    // TODO: ONE polymorphic loop printing each person's name, role and
    // monthly salary, followed by the total.
}

std::shared_ptr<Student> School::enrol(std::string studentName) {
    std::shared_ptr<Student> s = std::make_shared<Student>(studentName);
    roll.push_back(s);
    return s;
}

void School::studentLeaves(std::string studentName) {
    // TODO: remove the student's shared_ptr from the roll.
    (void)studentName;
}

} // namespace makersplace::school
