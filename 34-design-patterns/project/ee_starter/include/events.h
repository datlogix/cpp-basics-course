#pragma once

#include <string>

namespace makersplace::energy {

// OBSERVER: anything that wants to hear about sensor events implements this.
class SensorListener {
public:
    virtual ~SensorListener() = default;
    virtual void onSensorEvent(const std::string& sensorId, const std::string& kind, double value) = 0;
};

// STRATEGY: a way of pricing energy.
class Tariff {
public:
    virtual ~Tariff() = default;
    virtual std::string name() const = 0;
    virtual double costGhs(double kwh, int hourOfDay) const = 0;
};

// COMMAND: an undoable action from the app or remote.
class HomeCommand {
public:
    virtual ~HomeCommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string describe() const = 0;
};

} // namespace makersplace::energy
