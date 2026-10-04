// WARNING: this class is deliberately badly designed. Refactor it!
#pragma once

#include <iostream>
#include <string>
#include <vector>

class Buzzer {
public:
    void beep(std::string reason) { std::cout << "    [BUZZER] " << reason << std::endl; }
};

struct ApplianceRecord {
    std::string name;
    std::string type; // "fridge", "lighting", "aircon", "pump"
    double watts;
    double hours;
    int priority; // 1 = essential ... 3 = can be shed
};

class EnergyController {
public:
    std::vector<ApplianceRecord> appliances; // public data!
    std::string tariffBand = "residential";  // "lifeline", "residential", "commercial"
    Buzzer buzzer;

    void add(std::string name, std::string type, double watts, double hours, int priority);
    void runDay(double availableKw);
};
