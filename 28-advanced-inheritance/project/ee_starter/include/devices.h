// COMPOSITION CHECK (requirement 7): Could SmartPlug have been designed
// with composition instead of multiple inheritance? What would be gained
// and lost?
//
#pragma once

#include <string>

namespace makersplace::energy {

class Device {
protected:
    std::string serial;
    std::string location;

public:
    Device(std::string s, std::string loc);
    virtual ~Device();

    std::string getSerial() const { return serial; }
    virtual std::string describe() const = 0;
};

class PoweredDevice : public Device { // TODO (req 1): virtual inheritance
protected:
    double volts;
    double watts;
    bool on = true;

public:
    PoweredDevice(std::string s, std::string loc, double v, double w);
    virtual void emergencyShutdown(); // TODO (req 3): final
    std::string describe() const override;
};

class NetworkedDevice : public Device { // TODO (req 1): virtual inheritance
protected:
    std::string ipAddress;
    int signalStrengthDbm;

public:
    NetworkedDevice(std::string s, std::string loc, std::string ip, int dbm);
    void send(std::string message) const;
    std::string describe() const override;
};

// TODO (req 1): class SmartPlug : public PoweredDevice, public NetworkedDevice
//   - its constructor must construct Device directly
//   - describe() combines both: power use AND network details
//   - req 4: add send(double wattsReading) and fix the name hiding

// TODO (req 3): class SmartMeter final : public PoweredDevice, public NetworkedDevice

} // namespace makersplace::energy
