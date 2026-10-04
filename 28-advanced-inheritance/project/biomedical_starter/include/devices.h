// COMPOSITION CHECK (requirement 7): Could SmartWatchMonitor have been
// designed with composition instead of multiple inheritance? What would
// be gained and lost?
//
#pragma once

#include <string>

namespace makersplace::clinic {

class MedicalDevice {
protected:
    std::string serial;
    std::string patientFolder;

public:
    MedicalDevice(std::string s, std::string folder);
    virtual ~MedicalDevice();

    std::string getSerial() const { return serial; }
    virtual void alarm(std::string reason) const; // TODO (req 3): final
    virtual std::string status() const = 0;
};

class Wearable : public MedicalDevice { // TODO (req 1): virtual inheritance
protected:
    int batteryPercent;

public:
    Wearable(std::string s, std::string folder, int battery);
    bool needsCharging() const { return batteryPercent < 20; }
    std::string status() const override;
};

class WirelessDevice : public MedicalDevice { // TODO (req 1): virtual inheritance
protected:
    std::string bluetoothId;

public:
    WirelessDevice(std::string s, std::string folder, std::string btId);
    void transmit(std::string message) const;
    std::string status() const override;
};

// TODO (req 1): class SmartWatchMonitor : public Wearable, public WirelessDevice
//   - its constructor must construct MedicalDevice directly
//   - stores a heart rate; status() combines battery, Bluetooth and heart rate
//   - calls alarm() if the heart rate is outside 50..120 bpm
//   - req 4: add transmit(int heartRateBpm) and fix the name hiding

// TODO (req 3): class WirelessEcgPatch final : public Wearable, public WirelessDevice

} // namespace makersplace::clinic
