// Exercise 1: Composition, Aggregation & Association
//
// Model the computers in a school's ICT lab.
//
// TODO 1: class Computer is COMPOSED of a Processor and a Memory module,
//         held BY VALUE (they're built with the computer and die with it).
//         Its constructor takes a lab name, a processor speed (GHz), and a
//         memory size (GB), and passes them to the parts in its
//         initializer list.
// TODO 2: Computer is also COMPOSED of a polymorphic Storage part, held in
//         a std::unique_ptr<Storage>. Storage is an abstract base with
//         virtual std::string describe() const = 0, and derived classes
//         SolidStateDrive and HardDiskDrive. Pass the storage into the
//         constructor as a std::unique_ptr<Storage>.
// TODO 3: Computer AGGREGATES peripherals: a std::vector<Peripheral*> of
//         keyboards, mice, etc. that the LAB owns (in main). Add
//         void connect(Peripheral& p). Several computers may share one
//         peripheral over the day.
// TODO 4: Write a class TechnicianReport with a method
//         void print(const Computer& c) const that prints the computer's
//         full specification. TechnicianReport should only DEPEND on
//         Computer - it must not store it.
//         (Computer will need a const method to describe itself; use
//         DELEGATION to its parts.)
// TODO 5: In the UML comment block below, draw your design with the
//         correct relationship symbols and multiplicities.
// TODO 6: In main, build two computers, connect peripherals, print both
//         reports, and show (with destructor messages) that destroying a
//         computer destroys its processor/memory/storage but NOT the
//         peripherals.
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/*
  UML (TODO 5):

*/

class Processor {
    // TODO 1
};

class Memory {
    // TODO 1
};

class Storage {
    // TODO 2
};

class Peripheral {
private:
    std::string name;

public:
    explicit Peripheral(std::string n) : name(n) {}
    ~Peripheral() { std::cout << "  [-] peripheral " << name << std::endl; }
    std::string getName() const { return name; }
};

class Computer {
    // TODO 1, 2, 3
};

class TechnicianReport {
    // TODO 4
};

int main() {
    // TODO 6

    return 0;
}
