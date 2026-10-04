#include "course.h"
#include "teacher.h" // here we DO need Teacher's full definition (we call getName)

#include <iostream>

Course::Course(std::string t) : title(t) {}

void Course::setTeacher(Teacher& t) {
    teacher = &t;
}

void Course::print() const {
    std::cout << title << " is taught by "
              << (teacher != nullptr ? teacher->getName() : "nobody yet") << std::endl;
}
