#pragma once

#include <stdexcept>
#include <string>

namespace makersplace::school {

class SchoolError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class CourseFullError : public SchoolError {
private:
    std::string course;
    int capacity;

public:
    CourseFullError(std::string c, int cap)
        : SchoolError(c + " is full (capacity " + std::to_string(cap) + ")"), course(c), capacity(cap) {}
    std::string getCourse() const { return course; }
    int getCapacity() const { return capacity; }
};

// TODO: DuplicateEnrolmentError, PrerequisiteError (carries the missing
// prerequisite), StudentNotFoundError, CorruptRecordError

} // namespace makersplace::school
