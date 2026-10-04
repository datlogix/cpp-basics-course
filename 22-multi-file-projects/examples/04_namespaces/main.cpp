// Two different classes called Sensor live happily side by side,
// because each is inside its own namespace.
//
// Build and run (from inside this folder):
//   g++ -std=c++17 -Wall -Wextra main.cpp -o namespaces
//   ./namespaces
#include <iostream>
#include <string>

namespace robotics {

class Sensor {
public:
    std::string describe() const { return "robotics::Sensor - an ultrasonic distance sensor"; }
};

void greet() { std::cout << "Hello from the robotics namespace" << std::endl; }

} // namespace robotics

namespace clinic {

class Sensor {
public:
    std::string describe() const { return "clinic::Sensor - a pulse oximeter probe"; }
};

} // namespace clinic

// Namespaces can be nested (C++17 shorthand) and reopened later.
namespace makersplace::energy {

double kwh(double watts, double hours) { return watts * hours / 1000.0; }

} // namespace makersplace::energy

int main() {
    robotics::Sensor r;
    clinic::Sensor c;
    std::cout << r.describe() << std::endl;
    std::cout << c.describe() << std::endl;

    robotics::greet();

    std::cout << "A 1500 W kettle for 0.5 h uses "
              << makersplace::energy::kwh(1500, 0.5) << " kWh" << std::endl;

    // A using-DECLARATION brings in one name, only inside this function:
    using clinic::Sensor;
    Sensor another; // means clinic::Sensor here
    std::cout << another.describe() << std::endl;

    return 0;
}
