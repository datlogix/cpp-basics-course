#pragma once

#include <string>

namespace makersplace::clinic {

// The abstract base of the device hierarchy (Stage 2).
// VitalSignMonitor (and its subclasses) and InfusionPump derive from it.
class MedicalDevice {
protected:
    std::string serial;
    std::string bed;

public:
    MedicalDevice(std::string serialNumber, std::string bedLabel); // throws if the serial is empty
    virtual ~MedicalDevice() = default;

    std::string getId() const { return serial; }   // satisfies HasId for Repository<T>
    std::string getBed() const { return bed; }

    virtual std::string kind() const = 0;
    // TODO (Stage 2): more pure virtual behaviour your design needs
};

} // namespace makersplace::clinic
