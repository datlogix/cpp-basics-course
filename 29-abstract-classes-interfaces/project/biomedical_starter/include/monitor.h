#pragma once

#include "interfaces.h"

#include <memory>
#include <string>

namespace makersplace::clinic {

class VitalSignMonitor : public Alarmable, public Chartable {
protected:
    std::string bed;
    double simulatedValue; // stands in for a real sensor
    double lastValue = 0;
    std::string lastClass = "not checked";

    // Steps each monitor supplies:
    virtual double measure() const { return simulatedValue; }
    virtual std::string classify(double value) const = 0; // "normal", "warning", "critical"
    virtual std::string vitalName() const = 0;
    virtual std::string unit() const = 0;

public:
    VitalSignMonitor(std::string bedLabel, double value);

    // Template Method: measure -> classify -> record.
    void check();

    bool inAlarm() const override { return lastClass == "critical"; }
    std::string alarmMessage() const override;
    std::string chartEntry() const override;

    void setValue(double v) { simulatedValue = v; }
    void moveToBed(std::string bedLabel) { bed = bedLabel; }
    virtual std::unique_ptr<VitalSignMonitor> clone() const = 0;
};

class HeartRateMonitor : public VitalSignMonitor {
protected:
    std::string classify(double bpm) const override {
        if (bpm < 40 || bpm > 140) return "critical";
        if (bpm < 50 || bpm > 110) return "warning";
        return "normal";
    }
    std::string vitalName() const override { return "Heart rate"; }
    std::string unit() const override { return "bpm"; }

public:
    using VitalSignMonitor::VitalSignMonitor;
    std::unique_ptr<VitalSignMonitor> clone() const override {
        return std::make_unique<HeartRateMonitor>(*this);
    }
};

// TODO: class SpO2Monitor : public VitalSignMonitor        - critical < 88%, warning < 94%
// TODO: class TemperatureMonitor : public VitalSignMonitor - critical >= 40 or < 35 C, warning >= 38 C

// TODO: class FluidBalanceRecord : public Chartable - NOT a monitor: mL in, mL out, balance

} // namespace makersplace::clinic
