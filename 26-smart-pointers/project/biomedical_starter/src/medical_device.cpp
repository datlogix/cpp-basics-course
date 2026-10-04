#include "medical_device.h"

#include <iostream>
#include <sstream>

namespace makersplace::clinic {

MedicalDevice::MedicalDevice(std::string s) : serial(s) {}

MedicalDevice::~MedicalDevice() {
    std::cout << "  [-] device " << serial << std::endl;
}

std::string MedicalDevice::patientDescription() const {
    // TODO: lock() attachedTo. If it works, return the patient's name and
    // folder number; otherwise return "patient discharged - detach device".
    return "(unknown)";
}

Thermometer::Thermometer(std::string s, double c) : MedicalDevice(s), celsius(c) {}

std::string Thermometer::status() const {
    std::ostringstream out;
    out << "Thermometer " << serial << ": " << celsius << " C";
    return out.str();
}

bool Thermometer::needsAttention() const {
    // TODO
    return false;
}

PulseOximeter::PulseOximeter(std::string s, int spo2, int bpm)
    : MedicalDevice(s), spo2Percent(spo2), heartRateBpm(bpm) {}

std::string PulseOximeter::status() const {
    std::ostringstream out;
    out << "Pulse oximeter " << serial << ": SpO2 " << spo2Percent << "%, " << heartRateBpm << " bpm";
    return out.str();
}

bool PulseOximeter::needsAttention() const {
    // TODO
    return false;
}

InfusionPump::InfusionPump(std::string s, double rate, double remaining)
    : MedicalDevice(s), rateMlPerHour(rate), volumeRemainingMl(remaining) {}

std::string InfusionPump::status() const {
    std::ostringstream out;
    out << "Infusion pump " << serial << ": " << rateMlPerHour << " mL/h, " << volumeRemainingMl
        << " mL left";
    return out.str();
}

bool InfusionPump::needsAttention() const {
    // TODO
    return false;
}

} // namespace makersplace::clinic
