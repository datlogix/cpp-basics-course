#pragma once

#include <string>

namespace makersplace::school {

class Gradable {
public:
    virtual ~Gradable() = default;
    virtual double percentage() const = 0;
};

class Reportable {
public:
    virtual ~Reportable() = default;
    virtual std::string reportLine() const = 0;
};

} // namespace makersplace::school
