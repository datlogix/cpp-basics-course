// Some classes should NEVER be copied. = delete turns an accidental copy
// into a clear compile error instead of a hidden runtime bug.
#include <iostream>

class PowerSupply {
public:
    void switchOn() { std::cout << "  PSU ON" << std::endl; }
    void switchOff() { std::cout << "  PSU OFF" << std::endl; }
};

class SupplyGuard {
private:
    PowerSupply& supply;

public:
    explicit SupplyGuard(PowerSupply& psu) : supply(psu) { supply.switchOn(); }
    ~SupplyGuard() { supply.switchOff(); }

    // Two guards for one switch-on would switch the supply off twice.
    SupplyGuard(const SupplyGuard&) = delete;
    SupplyGuard& operator=(const SupplyGuard&) = delete;
};

// A class where the default copy is exactly right. = default documents
// that we THOUGHT about copying and chose the compiler's version.
class Reading {
private:
    double value;

public:
    explicit Reading(double v) : value(v) {}
    Reading(const Reading&) = default;
    Reading& operator=(const Reading&) = default;
    double get() const { return value; }
};

int main() {
    PowerSupply psu;
    {
        SupplyGuard guard(psu);
        // SupplyGuard copy = guard;   // ERROR: use of deleted function
        std::cout << "  testing..." << std::endl;
    }

    Reading r1(3.3);
    Reading r2 = r1; // fine
    std::cout << "Copied reading: " << r2.get() << std::endl;
    return 0;
}
