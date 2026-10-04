#pragma once

#include "interfaces.h"

#include <memory>
#include <string>

namespace makersplace::energy {

struct Reading { // a plain bundle of data (Module 8's guidance: struct for public data)
    double value;
    std::string unit;
    bool valid;
};

class Sensor : public Calibratable, public Alarmable {
protected:
    std::string serial;
    double offset = 0;
    int simulatedRaw; // stands in for a real ADC (0..1023)
    Reading last{0, "", true};

    // Steps each sensor supplies:
    virtual int readRaw() const { return simulatedRaw; }
    virtual double convert(int raw) const = 0;
    virtual std::string unit() const = 0;
    virtual bool inRange(double value) const = 0;

public:
    Sensor(std::string s, int raw);

    // Template Method: read -> convert -> apply offset -> check.
    Reading sample();

    void calibrate(double newOffset) override { offset = newOffset; }
    bool inAlarm() const override { return !last.valid; }
    std::string alarmMessage() const override;

    void setRaw(int raw) { simulatedRaw = raw; }
    void setSerial(std::string s) { serial = s; }
    virtual std::unique_ptr<Sensor> clone() const = 0;
};

class Thermistor : public Sensor {
protected:
    double convert(int raw) const override { return raw * 100.0 / 1023.0; } // simplified: 0-100 C
    std::string unit() const override { return "C"; }
    bool inRange(double v) const override { return v >= 0 && v <= 60; }

public:
    using Sensor::Sensor;
    std::unique_ptr<Sensor> clone() const override { return std::make_unique<Thermistor>(*this); }
};

// TODO: class CurrentSensor : public Sensor - 0..1023 maps to 0..30 A; in range below 20 A
// TODO: class LightSensor : public Sensor   - 0..1023 maps to 0..2000 lux; in range above 300 lux

// TODO: class CircuitBreaker : public Alarmable - NOT a Sensor; in alarm when tripped

} // namespace makersplace::energy
