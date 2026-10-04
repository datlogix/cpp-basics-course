#include "club.h"

#include <iostream>

namespace makersplace::school {

Club::Club(std::string n) : name(n) {}

void Club::join(const std::shared_ptr<Student>& s) {
    members.push_back(s); // a weak_ptr can be made from a shared_ptr
}

void Club::printRegister() const {
    std::cout << name << " register:" << std::endl;
    // TODO: for each weak_ptr, lock() it. Print the student's name if the
    // lock succeeds, otherwise "(left the school)".
}

} // namespace makersplace::school
