#pragma once

#include "circuit.h"

#include <string>
#include <vector>

namespace makersplace::energy {

class Alarm {
public:
    virtual ~Alarm() = default;
    virtual void raise(const std::string& circuit, double utilisation) = 0;
};

class LoadMonitor {
private:
    Alarm& alarm;

public:
    explicit LoadMonitor(Alarm& a) : alarm(a) {}
    int check(const std::vector<Circuit>& circuits); // raises for each circuit above 80%; returns how many
};

} // namespace makersplace::energy
