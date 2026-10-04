#include "student.h"

namespace makersplace::school {

int Student::nextId = 1;

Student::Student(std::string n) : id(nextId), name(n) {
    nextId++;
}

} // namespace makersplace::school
