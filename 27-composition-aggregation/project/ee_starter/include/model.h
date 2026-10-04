// Every class skeleton in one header, to get you started.
// TODO (Part 2): split into one .h/.cpp pair per class.
#pragma once

#include <memory>
#include <string>
#include <vector>

namespace makersplace::energy {

// ---------- Part 3: MISUSED INHERITANCE - fix this ----------
// Holds the load currents (amps) on one circuit.
// Rule: the TOTAL current must never exceed the breaker rating; a load
// that would exceed it must be refused.
class Circuit : public std::vector<double> {
private:
    double breakerAmps;

public:
    explicit Circuit(double breaker) : breakerAmps(breaker) {}
    double totalAmps() const;
};

class Appliance {
private:
    std::string name;
    double powerWatts;
    double hoursPerDay;

public:
    Appliance(std::string n, double watts, double hours);
    ~Appliance();
    std::string getName() const { return name; }
    double dailyKwh() const { return powerWatts * hoursPerDay / 1000.0; }
};

class Thermostat {
    // TODO: target temperature with a validated setter (Module 21)
};

class LightingCircuit {
    // TODO: number of bulbs, watts per bulb, hours per day
};

class Room {
private:
    std::string name;
    std::vector<std::unique_ptr<Appliance>> appliances; // composition (owns)
    // TODO: a Thermostat and a LightingCircuit (composition, by value)

public:
    explicit Room(std::string n);
    ~Room();
    Appliance& install(std::unique_ptr<Appliance> a); // returns a reference so the meter can observe it
};

class EnergyMeter {
private:
    std::vector<const Appliance*> monitored; // aggregation (observes, doesn't own)

public:
    void monitor(const Appliance& a);
    double dailyKwh() const;
};

class Electrician; // forward declaration

class House {
    // TODO: address, Rooms (composition), and Electrician* (association)
};

class Electrician {
    // TODO: name, the houses they service (association), and
    // void takeContract(House& h) - the ONE method that updates both sides
};

class BillCalculator {
    // TODO: double monthlyBillGhs(const EnergyMeter& m, double tariff) const - a dependency only
};

} // namespace makersplace::energy
