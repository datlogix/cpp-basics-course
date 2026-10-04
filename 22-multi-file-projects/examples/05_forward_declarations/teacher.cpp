#include "teacher.h"
#include "course.h"

#include <iostream>

Teacher::Teacher(std::string n) : name(n) {}

void Teacher::assignTo(Course& c) {
    course = &c;
    c.setTeacher(*this);
}

void Teacher::print() const {
    std::cout << name << " teaches "
              << (course != nullptr ? course->getTitle() : "nothing yet") << std::endl;
}
