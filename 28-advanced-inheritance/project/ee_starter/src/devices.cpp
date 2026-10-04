#include "devices.h"

#include <iostream>
#include <sstream>

namespace makersplace::energy {

Device::Device(std::string s, std::string loc) : serial(s), location(loc) {
    std::cout << "  [+] Device " << serial << std::endl;
}

Device::~Device() {}

PoweredDevice::PoweredDevice(std::string s, std::string loc, double v, double w)
    : Device(s, loc), volts(v), watts(w) {}

void PoweredDevice::emergencyShutdown() {
    on = false;
    std::cout << "  " << serial << ": EMERGENCY SHUTDOWN - power cut" << std::endl;
}

std::string PoweredDevice::describe() const {
    std::ostringstream out;
    out << serial << " (" << location << "): " << (on ? watts : 0) << " W at " << volts << " V";
    return out.str();
}

NetworkedDevice::NetworkedDevice(std::string s, std::string loc, std::string ip, int dbm)
    : Device(s, loc), ipAddress(ip), signalStrengthDbm(dbm) {}

void NetworkedDevice::send(std::string message) const {
    std::cout << "  " << serial << " -> " << ipAddress << ": " << message << std::endl;
}

std::string NetworkedDevice::describe() const {
    std::ostringstream out;
    out << serial << " (" << location << "): " << ipAddress << ", " << signalStrengthDbm << " dBm";
    return out.str();
}

} // namespace makersplace::energy
