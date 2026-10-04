// component.h - protected with CLASSIC include guards.
// (#pragma once would do the same job in one line.)
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component {
private:
    std::string label;

public:
    explicit Component(std::string l) : label(l) {} // short inline methods are fine in a header
    std::string getLabel() const { return label; }
};

#endif
