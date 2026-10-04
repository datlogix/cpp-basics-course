#pragma once

#include <map>
#include <string>

namespace makersplace::energy {

const double SUPPLY_VOLTS = 230.0;

class Circuit {
private:
    std::string name;
    double breakerAmps;
    std::map<std::string, double> loadWatts; // load name -> watts

public:
    Circuit(std::string n, double breaker); // throws if breaker <= 0

    // Throws std::invalid_argument for a duplicate name or watts <= 0, and
    // std::runtime_error if the new total current would be ABOVE the breaker
    // rating (exactly equal is allowed). On any throw, nothing changes.
    void addLoad(const std::string& loadName, double watts);
    bool removeLoad(const std::string& loadName);

    double totalAmps() const;
    double utilisation() const { return totalAmps() / breakerAmps; } // 0.0 .. 1.0
    int loadCount() const { return static_cast<int>(loadWatts.size()); }
    std::string getName() const { return name; }
};

} // namespace makersplace::energy
