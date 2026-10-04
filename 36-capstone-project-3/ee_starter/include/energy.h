#pragma once

#include <iostream>

namespace makersplace::energy {

// An amount of electrical energy, stored as whole watt-hours (Stage 1 and Stage 3).
class Energy {
private:
    long wattHours = 0;

public:
    Energy() = default;
    static Energy fromKwh(double kwh);
    static Energy fromPower(double watts, double hours);
    double kwh() const { return wattHours / 1000.0; }

    Energy& operator+=(const Energy& other);
    // TODO (Stage 3): -=, * (by a number of days), <=>, ==, >> ...

    friend std::ostream& operator<<(std::ostream& os, const Energy& e);
};

Energy operator+(Energy a, const Energy& b);

} // namespace makersplace::energy
