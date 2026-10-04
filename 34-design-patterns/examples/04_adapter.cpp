// ADAPTER: make a class with the "wrong" interface fit the interface
// your code expects - without changing either side.
#include <iostream>
#include <memory>
#include <vector>

// OUR interface, used throughout our program:
class TemperatureSensor {
public:
    virtual ~TemperatureSensor() = default;
    virtual double celsius() const = 0;
};

class Thermistor : public TemperatureSensor {
public:
    double celsius() const override { return 27.5; }
};

// A supplier's driver we CANNOT change: different name, units and type.
class FahrenheitProbe {
public:
    int readTenthsOfDegreeF() const { return 842; } // 84.2 F
};

// The ADAPTER: implements our interface by wrapping and translating.
class FahrenheitProbeAdapter : public TemperatureSensor {
private:
    const FahrenheitProbe& probe; // the "adaptee"

public:
    explicit FahrenheitProbeAdapter(const FahrenheitProbe& p) : probe(p) {}
    double celsius() const override {
        double f = probe.readTenthsOfDegreeF() / 10.0;
        return (f - 32) * 5.0 / 9.0;
    }
};

// Our existing code - unchanged, and unaware that one sensor is foreign.
void printTemperatures(const std::vector<const TemperatureSensor*>& sensors) {
    for (const TemperatureSensor* s : sensors) {
        std::cout << "  " << s->celsius() << " C" << std::endl;
    }
}

int main() {
    Thermistor ours;
    FahrenheitProbe supplierProbe;
    FahrenheitProbeAdapter adapted(supplierProbe);

    printTemperatures({&ours, &adapted});
    return 0;
}
