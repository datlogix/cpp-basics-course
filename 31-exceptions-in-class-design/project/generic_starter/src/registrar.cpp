#include "registrar.h"

#include <iostream>
#include <sstream>

namespace makersplace::school {

void Registrar::addCourse(const std::string& title, int capacity, const std::string& prerequisite) {
    if (capacity <= 0) {
        throw std::invalid_argument("course capacity must be positive");
    }
    courses[title] = Course{title, capacity, prerequisite};
}

int Registrar::loadStudents(std::istream& csv) {
    int loaded = 0;
    int lineNumber = 0;
    std::string line;
    while (std::getline(csv, line)) {
        lineNumber++;
        std::istringstream fields(line);
        std::string id, name, ageText;
        std::getline(fields, id, ',');
        std::getline(fields, name, ',');
        std::getline(fields, ageText, ',');

        // TODO: std::stoi can throw std::invalid_argument / std::out_of_range.
        // Translate them into CorruptRecordError (with lineNumber), report it,
        // and carry on with the next line.
        int age = std::stoi(ageText);
        students[id] = Student{id, name, age, {}};
        loaded++;
    }
    return loaded;
}

void Registrar::enrol(const std::string& studentId, const std::string& title) {
    // TODO: throw StudentNotFoundError, SchoolError (unknown course),
    // DuplicateEnrolmentError, PrerequisiteError, CourseFullError as needed,
    // and only then change anything.
    (void)studentId;
    (void)title;
}

void Registrar::enrolMany(const std::string& studentId, const std::vector<std::string>& titles) {
    // TODO: STRONG guarantee - validate everything first, then commit.
    (void)studentId;
    (void)titles;
}

void Registrar::print() const {
    for (const auto& entry : courses) {
        const Course& c = entry.second;
        std::cout << "  " << c.title << ": " << c.enrolled << "/" << c.capacity << std::endl;
    }
}

} // namespace makersplace::school
