#include "devices.h"

#include <iostream>
#include <sstream>

namespace makersplace::clinic {

MedicalDevice::MedicalDevice(std::string s, std::string folder) : serial(s), patientFolder(folder) {
    std::cout << "  [+] MedicalDevice " << serial << std::endl;
}

MedicalDevice::~MedicalDevice() {}

void MedicalDevice::alarm(std::string reason) const {
    std::cout << "  *** ALARM " << serial << " (patient " << patientFolder << "): " << reason
              << " ***" << std::endl;
}

Wearable::Wearable(std::string s, std::string folder, int battery)
    : MedicalDevice(s, folder), batteryPercent(battery) {}

std::string Wearable::status() const {
    std::ostringstream out;
    out << serial << ": battery " << batteryPercent << "%" << (needsCharging() ? " (CHARGE ME)" : "");
    return out.str();
}

WirelessDevice::WirelessDevice(std::string s, std::string folder, std::string btId)
    : MedicalDevice(s, folder), bluetoothId(btId) {}

void WirelessDevice::transmit(std::string message) const {
    std::cout << "  " << serial << " [" << bluetoothId << "] -> ward station: " << message << std::endl;
}

std::string WirelessDevice::status() const {
    return serial + ": Bluetooth " + bluetoothId;
}

} // namespace makersplace::clinic
