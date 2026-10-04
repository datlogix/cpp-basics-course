#pragma once

#include <string>

namespace makersplace::school {

class StaffMember {
protected:
    std::string name;

public:
    explicit StaffMember(std::string n);
    virtual ~StaffMember();

    std::string getName() const { return name; }
    virtual std::string role() const = 0;           // every kind of staff must say its role
    virtual double monthlySalaryGhs() const = 0;    // ...and how its salary is worked out
};

class Teacher : public StaffMember {
private:
    double baseSalary;
    int subjectsTaught;

public:
    Teacher(std::string n, double base, int subjects);
    std::string role() const override;
    double monthlySalaryGhs() const override; // TODO: base + 150 per subject
};

class Administrator : public StaffMember {
private:
    double fixedSalary;

public:
    Administrator(std::string n, double salary);
    std::string role() const override;
    double monthlySalaryGhs() const override;
};

} // namespace makersplace::school
