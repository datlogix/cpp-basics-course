#pragma once

#include "patient.h"

#include <memory>
#include <string>

namespace makersplace::clinic {

class MedicalDevice {
protected:
    std::string serial;
    std::weak_ptr<Patient> attachedTo; // OBSERVES the patient - doesn't keep them admitted

public:
    explicit MedicalDevice(std::string s);
    virtual ~MedicalDevice();

    std::string getSerial() const { return serial; }
    void attach(const std::shared_ptr<Patient>& p) { attachedTo = p; }
    std::string patientDescription() const; // TODO: lock(); name, or "patient discharged - detach device"

    virtual std::string status() const = 0;
    virtual bool needsAttention() const = 0;
};

class Thermometer : public MedicalDevice {
private:
    double celsius;

public:
    Thermometer(std::string s, double c);
    std::string status() const override;
    bool needsAttention() const override; // TODO: fever >= 38.0 or < 35.0
};

class PulseOximeter : public MedicalDevice {
private:
    int spo2Percent;
    int heartRateBpm;

public:
    PulseOximeter(std::string s, int spo2, int bpm);
    std::string status() const override;
    bool needsAttention() const override; // TODO: SpO2 < 92 or bpm outside 50..120
};

class InfusionPump : public MedicalDevice {
private:
    double rateMlPerHour;
    double volumeRemainingMl;

public:
    InfusionPump(std::string s, double rate, double remaining);
    std::string status() const override;
    bool needsAttention() const override; // TODO: less than 1 hour of fluid left
};

} // namespace makersplace::clinic
