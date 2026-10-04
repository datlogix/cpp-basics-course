#pragma once

#include "appliance.h"

#include <memory>
#include <string>
#include <vector>

namespace makersplace::energy {

class Room {
private:
    std::string name;
    std::vector<std::unique_ptr<Appliance>> appliances; // OWNS its appliances

public:
    explicit Room(std::string n);
    ~Room();

    std::string getName() const { return name; }
    void install(std::unique_ptr<Appliance> a);
    std::unique_ptr<Appliance> remove(std::string applianceName); // TODO
    double dailyKwh() const;                                      // TODO
    void printReport() const;                                     // TODO
};

} // namespace makersplace::energy
