// Module 20 Project - Track B: Home Energy Monitor
// See project/README.md for the problem statement.
//
// Write DESIGN.md FIRST. Then fill in these classes so they match it.
#include <iostream>
#include <string>
#include <vector>

const double TARIFF_GHS_PER_KWH = 1.80; // example tariff - use a real one if you know it
const int DAYS_PER_MONTH = 30;

class Appliance {
    // TODO: name, power rating (W), hours per day
    // TODO: double dailyKwh() const  -> powerWatts * hoursPerDay / 1000.0
};

class Room {
    // TODO: name, appliances
    // TODO: bool addAppliance(...) - refuses negative watts or hours outside 0..24
    // TODO: double dailyKwh() const - total of its appliances
    // TODO: void printReport() const
};

class House {
    // TODO: rooms
    // TODO: double dailyKwh() const, double monthlyCostGhs() const
    // TODO: void printReport() const
};

int main() {
    // TODO: build a house with at least two rooms, two appliances each
    // TODO: show that an invalid appliance is refused
    // TODO: print the per-room and whole-house report with monthly cost

    return 0;
}
