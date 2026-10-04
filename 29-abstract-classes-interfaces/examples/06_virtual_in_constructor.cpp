// During a base class's constructor (and destructor), the derived part
// doesn't exist, so virtual calls go to the BASE version.
#include <iostream>
#include <string>

class Sensor {
public:
    Sensor() { std::cout << "  Sensor constructor sees: " << kind() << std::endl; }
    virtual ~Sensor() { std::cout << "  Sensor destructor sees: " << kind() << std::endl; }
    virtual std::string kind() const { return "generic sensor"; }
};

class Thermistor : public Sensor {
public:
    Thermistor() { std::cout << "  Thermistor constructor sees: " << kind() << std::endl; }
    ~Thermistor() override { std::cout << "  Thermistor destructor sees: " << kind() << std::endl; }
    std::string kind() const override { return "thermistor"; }
};

int main() {
    std::cout << "Creating a Thermistor:" << std::endl;
    {
        Thermistor t;
        std::cout << "  After construction, t.kind() = " << t.kind() << std::endl;
        std::cout << "Destroying it:" << std::endl;
    }
    return 0;
}
