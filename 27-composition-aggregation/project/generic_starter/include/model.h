// Every class skeleton in one header, to get you started.
// TODO (Part 2): split into one .h/.cpp pair per class.
#pragma once

#include <memory>
#include <string>
#include <vector>

namespace makersplace::school {

// ---------- Part 3: MISUSED INHERITANCE - fix this ----------
// Rule: scores must be between 0 and 100.
class Gradebook : public std::vector<double> {
public:
    double average() const;
};

class Student {
private:
    std::string name;

public:
    explicit Student(std::string n);
    ~Student();
    std::string getName() const { return name; }
};

class Teacher; // forward declaration: Course only points to a Teacher

class Course {
private:
    std::string title;
    Teacher* teacher = nullptr;      // association (the other side lives in Teacher)
    std::vector<Student*> students;  // aggregation
    // TODO: a Gradebook member (composition) once Part 3 is done

public:
    explicit Course(std::string t);
    ~Course();
    std::string getTitle() const { return title; }
    void enrol(Student& s);
    void printRegister() const;
    // TODO: what does Course need so that Teacher can keep BOTH sides consistent?
};

class Teacher {
private:
    std::string name;
    std::vector<Course*> courses;    // association

public:
    explicit Teacher(std::string n);
    std::string getName() const { return name; }
    void assign(Course& c); // TODO: the ONE method that updates both sides
};

class Timetable {
    // TODO: e.g. a list of "day period course" strings
};

class Classroom {
    // TODO: name, capacity, and a Timetable (composition)
};

class School {
    // TODO: name, and its Classrooms (composition)
};

class ReportCardPrinter {
    // TODO: void print(const Course& c) const - a dependency only
};

} // namespace makersplace::school
