#pragma once

namespace makersplace::energy {

// A (simulated) bench power supply. Provided complete - don't change it.
class PowerSupply {
private:
    bool on = false;
    double volts = 0;

public:
    void switchOn(double v);
    void switchOff();
    bool isOn() const { return on; }
    double getVolts() const { return volts; }
};

} // namespace makersplace::energy
