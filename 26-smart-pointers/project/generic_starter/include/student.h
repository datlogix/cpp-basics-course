#pragma once

#include <iostream>
#include <string>

namespace makersplace::school {

class Student {
private:
    std::string name;

public:
    explicit Student(std::string n) : name(n) {}
    ~Student() { std::cout << "  [-] student " << name << std::endl; }
    std::string getName() const { return name; }
};

} // namespace makersplace::school
