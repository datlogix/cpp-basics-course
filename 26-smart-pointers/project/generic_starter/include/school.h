#pragma once

#include "staff.h"
#include "student.h"

#include <memory>
#include <string>
#include <vector>

namespace makersplace::school {

class School {
private:
    std::string name;
    std::vector<std::unique_ptr<StaffMember>> staff;  // OWNS staff
    std::vector<std::shared_ptr<Student>> roll;       // SHARES students (clubs observe them)

public:
    explicit School(std::string n);

    void hire(std::unique_ptr<StaffMember> person);
    std::unique_ptr<StaffMember> release(std::string staffName); // TODO
    void printPayroll() const;                                    // TODO

    std::shared_ptr<Student> enrol(std::string studentName);
    void studentLeaves(std::string studentName);                  // TODO
};

} // namespace makersplace::school
