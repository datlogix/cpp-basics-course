// Open/Closed Principle: add new behaviour by ADDING code, not editing it.
// BEFORE: a switch on a type code that must be edited for every new appliance.
// AFTER:  each appliance knows its own behaviour; new kinds are added freely.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

const double TARIFF = 1.80; // GHS per kWh

namespace before {

enum class Kind { Fridge, Television, AirConditioner };

struct Appliance {
    std::string name;
    Kind kind;
    double watts;
    double hours;
    double duty;
};

double dailyKwh(const Appliance& a) {
    switch (a.kind) { // EVERY new kind means editing this - and every switch like it
        case Kind::Fridge:         return a.watts * 24 / 1000.0;
        case Kind::Television:     return a.watts * a.hours / 1000.0;
        case Kind::AirConditioner: return a.watts * a.hours * a.duty / 1000.0;
    }
    return 0;
}

} // namespace before

namespace after {

class Appliance {
protected:
    std::string name;
    double watts;

public:
    Appliance(std::string n, double w) : name(n), watts(w) {}
    virtual ~Appliance() = default;
    std::string getName() const { return name; }
    virtual double dailyKwh() const = 0;
};

class Fridge : public Appliance {
public:
    using Appliance::Appliance;
    double dailyKwh() const override { return watts * 24 / 1000.0; }
};

class Television : public Appliance {
    double hours;
public:
    Television(std::string n, double w, double h) : Appliance(n, w), hours(h) {}
    double dailyKwh() const override { return watts * hours / 1000.0; }
};

// ADDED LATER - not a single line of existing code was edited:
class SolarWaterHeater : public Appliance {
    double backupHours;
public:
    SolarWaterHeater(std::string n, double w, double h) : Appliance(n, w), backupHours(h) {}
    double dailyKwh() const override { return watts * backupHours * 0.2 / 1000.0; } // mostly solar
};

double monthlyCost(const Appliance& a) { // closed for modification
    return a.dailyKwh() * 30 * TARIFF;
}

} // namespace after

int main() {
    before::Appliance tv{"TV", before::Kind::Television, 90, 5, 1};
    std::cout << "before: TV uses " << before::dailyKwh(tv) << " kWh/day" << std::endl;

    std::vector<std::unique_ptr<after::Appliance>> home;
    home.push_back(std::make_unique<after::Fridge>("Fridge", 150));
    home.push_back(std::make_unique<after::Television>("TV", 90, 5));
    home.push_back(std::make_unique<after::SolarWaterHeater>("Water heater", 3000, 2));
    for (const auto& a : home) {
        std::cout << "after:  " << a->getName() << " costs GHS " << after::monthlyCost(*a) << "/month"
                  << std::endl;
    }
    return 0;
}
