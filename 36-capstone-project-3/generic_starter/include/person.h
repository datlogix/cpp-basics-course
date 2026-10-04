#pragma once

#include <string>

namespace makersplace::school {

// The abstract base of the people hierarchy (Stage 2).
// Student, Teacher and Administrator derive from it.
class Person {
protected:
    std::string id;
    std::string name;

public:
    Person(std::string personId, std::string personName); // throws if either is empty
    virtual ~Person() = default;

    std::string getId() const { return id; }   // satisfies HasId for Repository<T>
    std::string getName() const { return name; }

    virtual std::string role() const = 0;
    // TODO (Stage 2): more pure virtual behaviour your design needs
};

} // namespace makersplace::school
