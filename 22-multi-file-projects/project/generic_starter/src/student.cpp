// src/student.cpp - MODEL CLASS definitions.
#include "student.h"

#include <iostream> // only the .cpp prints, so only the .cpp includes iostream

namespace makersplace::school {

int Student::nextId = 1; // static data member: defined once, in the .cpp

Student::Student(std::string n, std::string f) : id(nextId), name(n), form(f) {
    nextId++;
}

Student::Student(std::string n) : Student(n, "Unassigned") {}

void Student::print() const {
    std::cout << "#" << id << " " << name << " (" << form << ")" << std::endl;
}

} // namespace makersplace::school
