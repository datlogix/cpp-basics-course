#pragma once

#include "student.h"

#include <memory>
#include <string>
#include <vector>

namespace makersplace::school {

class Club {
private:
    std::string name;
    std::vector<std::weak_ptr<Student>> members; // OBSERVES students - doesn't keep them alive

public:
    explicit Club(std::string n);
    void join(const std::shared_ptr<Student>& s);
    void printRegister() const; // TODO
};

} // namespace makersplace::school
