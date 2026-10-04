// course.h - Course needs to know about Teacher, and teacher.h needs to
// know about Course. A forward declaration breaks the include cycle.
#pragma once

#include <string>

class Teacher; // forward declaration: "a class called Teacher exists"

class Course {
private:
    std::string title;
    Teacher* teacher = nullptr; // pointer only - the full class isn't needed here

public:
    explicit Course(std::string t);
    void setTeacher(Teacher& t);
    void print() const; // needs Teacher's members, so course.cpp includes teacher.h
    std::string getTitle() const { return title; }
};
