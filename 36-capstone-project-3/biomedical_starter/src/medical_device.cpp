#include "medical_device.h"

#include <stdexcept>

namespace makersplace::clinic {

MedicalDevice::MedicalDevice(std::string serialNumber, std::string bedLabel)
    : serial(serialNumber), bed(bedLabel) {
    if (serial.empty()) {
        throw std::invalid_argument("a device needs a serial number");
    }
}

} // namespace makersplace::clinic
