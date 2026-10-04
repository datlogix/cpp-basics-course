#include "model.h"

#include <iostream>

namespace makersplace::school {

double Gradebook::average() const {
    if (empty()) {
        return 0;
    }
    double total = 0;
    for (double s : *this) {
        total += s;
    }
    return total / size();
}

Student::Student(std::string n) : name(n) {}
Student::~Student() { std::cout << "  [-] student " << name << std::endl; }

Course::Course(std::string t) : title(t) {}
Course::~Course() { std::cout << "  [-] course " << title << std::endl; }

void Course::enrol(Student& s) {
    students.push_back(&s);
}

void Course::printRegister() const {
    std::cout << title << " (teacher: " << "TODO" << "):";
    for (const Student* s : students) {
        std::cout << " " << s->getName();
    }
    std::cout << std::endl;
}

Teacher::Teacher(std::string n) : name(n) {}

void Teacher::assign(Course& c) {
    // TODO: remove c from its previous teacher's list (if any), add it to
    // this teacher's list, and set c's teacher to this teacher.
    courses.push_back(&c);
}

} // namespace makersplace::school
