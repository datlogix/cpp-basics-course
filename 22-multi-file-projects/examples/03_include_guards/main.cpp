// main.cpp includes component.h directly AND indirectly (through
// circuit.h). The include guards make the second inclusion a no-op.
//
// Build and run (from inside this folder):
//   g++ -std=c++17 -Wall -Wextra main.cpp circuit.cpp -o circuit
//   ./circuit
//
// Experiment: delete the three guard lines from component.h and rebuild
// to see the "redefinition of 'class Component'" error.
#include "component.h"
#include "circuit.h"

#include <iostream>

int main() {
    Circuit c;
    c.add(Component("R1: 220 ohm resistor"));
    c.add(Component("LED1: red LED"));
    c.add(Component("SW1: push button"));

    std::cout << "Circuit parts:" << std::endl;
    c.print();
    return 0;
}
