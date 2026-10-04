// WARNING: this class is deliberately badly designed. Refactor it!
// (The scoring rules are simplified for teaching - not for clinical use.)
#pragma once

#include <iostream>
#include <string>
#include <vector>

class Pager {
public:
    void page(std::string who, std::string text) { std::cout << "    [PAGE " << who << "] " << text << std::endl; }
};

struct PatientRecord {
    std::string bed;
    std::string name;
    std::vector<std::string> vitalTypes; // "hr", "temp", "spo2", "sbp"
    std::vector<double> values;
};

class WardManager {
public:
    std::vector<PatientRecord> patients; // public data!
    std::string wardName;
    Pager pager;

    void admit(std::string bed, std::string name);
    void record(std::string bed, std::string type, double value);
    void doShift();
};
