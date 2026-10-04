#include "people.h"

#include <iostream>

namespace makersplace::school {

Person::Person(std::string personId, std::string n) : id(personId), name(n) {
    std::cout << "  [+] Person " << name << std::endl;
}

Person::~Person() {}

void Person::idCard() const {
    std::cout << "  +------------------------------+" << std::endl;
    std::cout << "  | MAKERSPLACE ID  " << id << std::endl;
    std::cout << "  | " << name << " - " << role() << std::endl;
    std::cout << "  +------------------------------+" << std::endl;
}

Teacher::Teacher(std::string personId, std::string n, double salary)
    : Person(personId, n), baseSalary(salary) {}

void Teacher::assign(std::string course) {
    courses.push_back(course);
}

double Teacher::monthlySalaryGhs() const {
    return baseSalary;
}

Researcher::Researcher(std::string personId, std::string n, double grant)
    : Person(personId, n), grantGhs(grant) {}

void Researcher::publish(std::string title) {
    publications.push_back(title);
}

} // namespace makersplace::school
