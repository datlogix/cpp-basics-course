#pragma once

#include <string>

namespace makersplace::school {

class Student {
private:
    static int nextId;

    const int id;
    std::string name;

public:
    explicit Student(std::string n);

    int getId() const { return id; }
    std::string getName() const { return name; }
};

} // namespace makersplace::school
