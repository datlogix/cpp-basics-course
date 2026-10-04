#include "circuit.h"

#include <iostream>

void Circuit::add(const Component& c) {
    parts.push_back(c);
}

void Circuit::print() const {
    for (const Component& c : parts) {
        std::cout << " - " << c.getLabel() << std::endl;
    }
}
