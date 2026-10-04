// include/student.h - MODEL CLASS: study this, then split Club the same way.
#pragma once

#include <string> // needed here because members are std::string

namespace makersplace::school {

class Student {
private:
    static int nextId;

    const int id;
    std::string name;
    std::string form;

public:
    Student(std::string n, std::string f);
    explicit Student(std::string n);

    // One-line getters may stay inline in the header.
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getForm() const { return form; }

    void print() const;
};

} // namespace makersplace::school
