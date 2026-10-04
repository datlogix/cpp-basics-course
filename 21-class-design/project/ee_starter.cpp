// Module 21 Project - Track B: Home Energy Monitor, redesigned
// See project/README.md for requirements.
#include <iostream>
#include <string>

const int DAYS_PER_MONTH = 30;

class Appliance {
private:
    // INVARIANT: powerWatts > 0 and 0 <= hoursPerDay <= 24.
    static double tariffGhsPerKwh;

    const std::string name;
    const double powerWatts;
    double hoursPerDay = 1.0;

    static double safePower(double watts); // helper used in the initializer list

public:
    Appliance(std::string n, double watts, double hours);
    // TODO: make this delegate to the three-argument constructor (100 W, 1 hour)
    explicit Appliance(std::string n) : name(n), powerWatts(100.0) {}

    bool useFor(double hours);         // TODO: validate 0..24
    double dailyKwh() const;           // TODO
    double monthlyCostGhs() const;     // TODO: uses the static tariff
    void print() const;                // TODO

    static bool setTariff(double ghsPerKwh); // TODO: reject <= 0
    static double getTariff() { return tariffGhsPerKwh; }
};

double Appliance::tariffGhsPerKwh = 1.80;

double Appliance::safePower(double watts) {
    if (watts <= 0) {
        std::cout << "Warning: invalid power " << watts << " W, using 100 W" << std::endl;
        return 100.0;
    }
    return watts;
}

Appliance::Appliance(std::string n, double watts, double hours)
    : name(n), powerWatts(safePower(watts)) {
    if (!useFor(hours)) {
        std::cout << "Warning: invalid hours " << hours << ", using 1 hour" << std::endl;
    }
}

bool Appliance::useFor(double hours) {
    // TODO: return false (changing nothing) if hours is outside 0..24
    (void)hours;
    return true;
}

double Appliance::dailyKwh() const {
    // TODO: powerWatts * hoursPerDay / 1000.0
    return 0;
}

double Appliance::monthlyCostGhs() const {
    // TODO: dailyKwh() * DAYS_PER_MONTH * tariffGhsPerKwh
    return 0;
}

void Appliance::print() const {
    // TODO: name, watts, hours/day, kWh/day, monthly cost
}

bool Appliance::setTariff(double ghsPerKwh) {
    // TODO: reject <= 0
    (void)ghsPerKwh;
    return false;
}

int main() {
    Appliance fridge("Fridge", 150, 24);
    Appliance fan("Ceiling fan", 75, 10);
    Appliance broken("Mystery device", -40, 30); // should warn twice

    // TODO: print each appliance, change the tariff (and try an invalid one),
    // and print the monthly cost of each appliance again.

    return 0;
}
