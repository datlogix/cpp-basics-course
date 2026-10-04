// circuit.h - ALSO includes component.h. Without guards, main.cpp
// (which includes both headers) would see class Component twice.
#pragma once

#include "component.h"

#include <vector>

class Circuit {
private:
    std::vector<Component> parts;

public:
    void add(const Component& c);
    void print() const;
};
