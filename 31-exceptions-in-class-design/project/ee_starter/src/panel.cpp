#include "panel.h"

#include <iostream>
#include <sstream>

namespace makersplace::energy {

void Panel::addCircuit(const std::string& name, double breakerAmps) {
    if (breakerAmps <= 0) {
        throw std::invalid_argument("breaker rating must be positive");
    }
    circuits[name] = Circuit{name, breakerAmps, {}};
}

int Panel::loadAppliances(std::istream& csv) {
    int loaded = 0;
    int lineNumber = 0;
    std::string line;
    while (std::getline(csv, line)) {
        lineNumber++;
        std::istringstream fields(line);
        std::string circuit, name, wattsText;
        std::getline(fields, circuit, ',');
        std::getline(fields, name, ',');
        std::getline(fields, wattsText, ',');

        // TODO: translate std::stod failures into CorruptRecordError (with
        // lineNumber), and an unknown circuit into UnknownCircuitError;
        // report them and carry on with the next line.
        double watts = std::stod(wattsText);
        circuits.at(circuit).loads.push_back(Load{name, watts});
        loaded++;
    }
    return loaded;
}

double Panel::currentOn(const std::string& circuit) const {
    // TODO
    (void)circuit;
    return 0;
}

void Panel::applySchedule(const std::vector<LoadChange>& changes) {
    // TODO: STRONG guarantee - work out every circuit's NEW current first
    // (on a copy, or by calculation), throw OvercurrentError if any would
    // exceed its breaker, and only then switch the loads.
    (void)changes;
}

void Panel::print() const {
    for (const auto& entry : circuits) {
        const Circuit& c = entry.second;
        std::cout << "  " << c.name << " (" << c.breakerAmps << " A breaker):";
        for (const Load& l : c.loads) {
            std::cout << " " << l.name << (l.on ? "[ON]" : "[off]");
        }
        std::cout << std::endl;
    }
}

} // namespace makersplace::energy
