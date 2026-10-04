#pragma once

#include "errors.h"

#include <istream>
#include <map>
#include <string>
#include <vector>

namespace makersplace::school {

struct Student {
    std::string id;
    std::string name;
    int age;
    std::vector<std::string> courses; // titles this student is enrolled in
};

struct Course {
    std::string title;
    int capacity;
    std::string prerequisite; // empty if none
    int enrolled = 0;
};

class Registrar {
private:
    std::map<std::string, Student> students;
    std::map<std::string, Course> courses;

public:
    // GUARANTEE: ...
    void addCourse(const std::string& title, int capacity, const std::string& prerequisite = "");

    // GUARANTEE: ...
    int loadStudents(std::istream& csv); // returns how many loaded; TODO: translate errors

    // GUARANTEE: ...
    void enrol(const std::string& studentId, const std::string& title); // TODO

    // GUARANTEE: strong
    void enrolMany(const std::string& studentId, const std::vector<std::string>& titles); // TODO

    // GUARANTEE: ...
    void print() const;
};

} // namespace makersplace::school
