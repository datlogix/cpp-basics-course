#pragma once

#include "errors.h"

#include <istream>
#include <map>
#include <string>
#include <vector>

namespace makersplace::energy {

const double SUPPLY_VOLTS = 230.0;

struct Load {
    std::string name;
    double watts;
    bool on = false;
};

struct Circuit {
    std::string name;
    double breakerAmps;
    std::vector<Load> loads;
};

struct LoadChange { // one entry in an evening switching schedule
    std::string circuit;
    std::string load;
    bool switchOn;
};

class Panel {
private:
    std::map<std::string, Circuit> circuits;

public:
    // GUARANTEE: ...
    void addCircuit(const std::string& name, double breakerAmps);

    // GUARANTEE: ...
    int loadAppliances(std::istream& csv); // TODO: translate errors

    // GUARANTEE: ...
    double currentOn(const std::string& circuit) const; // TODO: sum of watts of loads that are on / 230

    // GUARANTEE: strong
    void applySchedule(const std::vector<LoadChange>& changes); // TODO

    // GUARANTEE: ...
    void print() const;
};

} // namespace makersplace::energy
