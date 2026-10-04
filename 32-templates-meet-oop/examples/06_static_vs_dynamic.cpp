// The same feature - "describe a sensor" - written three ways:
//   A. dynamic polymorphism (virtual)       - decided at RUNTIME
//   B. static polymorphism (a template)     - decided at COMPILE TIME
//   C. CRTP (shared base code, still static)
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ---------- A. virtual ----------
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual std::string name() const = 0;
    virtual double read() const = 0;
};

class Thermometer : public Sensor {
public:
    std::string name() const override { return "thermometer"; }
    double read() const override { return 28.5; }
};

class Hygrometer : public Sensor {
public:
    std::string name() const override { return "hygrometer"; }
    double read() const override { return 64.0; }
};

void describeDynamic(const Sensor& s) {
    std::cout << "  [dynamic] " << s.name() << " reads " << s.read() << std::endl;
}

// ---------- B. template ----------
// These two types share NO base class. They just both have name() and read().
struct LightMeter {
    std::string name() const { return "light meter"; }
    double read() const { return 540.0; }
};

struct Anemometer {
    std::string name() const { return "anemometer"; }
    double read() const { return 3.2; }
};

template <typename S>
void describeStatic(const S& s) {
    std::cout << "  [static]  " << s.name() << " reads " << s.read() << std::endl;
}

// ---------- C. CRTP ----------
template <typename Derived>
class Describable {
public:
    void describe() const {
        const Derived& self = static_cast<const Derived&>(*this);
        std::cout << "  [CRTP]    " << self.name() << " reads " << self.read() << std::endl;
    }
};

class RainGauge : public Describable<RainGauge> { // "curiously recurring"
public:
    std::string name() const { return "rain gauge"; }
    double read() const { return 12.5; }
};

int main() {
    std::vector<std::unique_ptr<Sensor>> sensors; // a MIXED collection needs dynamic polymorphism
    sensors.push_back(std::make_unique<Thermometer>());
    sensors.push_back(std::make_unique<Hygrometer>());
    for (const auto& s : sensors) {
        describeDynamic(*s);
    }

    describeStatic(LightMeter()); // the compiler writes describeStatic<LightMeter>
    describeStatic(Anemometer()); // ...and describeStatic<Anemometer>
    describeStatic(Thermometer()); // works too - it has name() and read()

    RainGauge gauge;
    gauge.describe(); // base-class code, resolved at compile time
    return 0;
}
