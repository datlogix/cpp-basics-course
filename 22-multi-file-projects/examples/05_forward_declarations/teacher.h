// teacher.h
#pragma once

#include <string>

class Course; // forward declaration

class Teacher {
private:
    std::string name;
    Course* course = nullptr;

public:
    explicit Teacher(std::string n);
    void assignTo(Course& c); // reference only - forward declaration is enough
    std::string getName() const { return name; }
    void print() const;
};
