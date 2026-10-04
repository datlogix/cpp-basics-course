#pragma once

#include <string>

namespace makersplace::energy {

class Appliance {
protected:
    std::string name;
    double powerWatts;

public:
    Appliance(std::string n, double watts);
    virtual ~Appliance();

    std::string getName() const { return name; }
    virtual double dailyKwh() const = 0;
    virtual std::string kind() const = 0;
};

class AlwaysOnAppliance : public Appliance { // e.g. a fridge: 24 h/day
public:
    AlwaysOnAppliance(std::string n, double watts);
    double dailyKwh() const override;
    std::string kind() const override { return "always on"; }
};

class TimedAppliance : public Appliance { // e.g. a TV: some hours per day
private:
    double hoursPerDay;

public:
    TimedAppliance(std::string n, double watts, double hours);
    double dailyKwh() const override; // TODO
    std::string kind() const override { return "timed"; }
};

class ThermostaticAppliance : public Appliance { // e.g. an AC: compressor cycles on/off
private:
    double hoursPerDay;
    double dutyCycle; // fraction of the time the compressor actually runs, 0..1

public:
    ThermostaticAppliance(std::string n, double watts, double hours, double duty);
    double dailyKwh() const override; // TODO: watts * hours * duty / 1000
    std::string kind() const override { return "thermostatic"; }
};

} // namespace makersplace::energy
