// COMPOSITION CHECK (requirement 7): Could TeachingResearcher have been
// designed with composition instead of multiple inheritance? What would
// be gained and lost?
//
#pragma once

#include <string>
#include <vector>

namespace makersplace::school {

class Person {
protected:
    std::string id;
    std::string name;

public:
    Person(std::string personId, std::string n);
    virtual ~Person();

    std::string getName() const { return name; }
    void idCard() const;                         // TODO (req 3): make this final - hint: it must be virtual to be final
    virtual double monthlySalaryGhs() const = 0;
    virtual std::string role() const = 0;
};

class Teacher : public Person { // TODO (req 1): virtual inheritance
protected:
    double baseSalary;
    std::vector<std::string> courses;

public:
    Teacher(std::string personId, std::string n, double salary);
    void assign(std::string course);
    double monthlySalaryGhs() const override;
    std::string role() const override { return "Teacher"; }
};

class Researcher : public Person { // TODO (req 1): virtual inheritance
protected:
    double grantGhs;
    std::vector<std::string> publications;

public:
    Researcher(std::string personId, std::string n, double grant);
    void publish(std::string title);
    double monthlySalaryGhs() const override { return 0; } // paid from the grant, not salary
    std::string role() const override { return "Researcher"; }
};

// TODO (req 1): class TeachingResearcher : public Teacher, public Researcher
//   - its constructor must construct Person directly
//   - monthlySalaryGhs() = baseSalary + 10% of grantGhs
//   - role() = "Teaching researcher"
//   - req 4: add assign(std::string course, int periodsPerWeek) and fix the name hiding

// TODO (req 3): class Principal final : public Teacher

} // namespace makersplace::school
