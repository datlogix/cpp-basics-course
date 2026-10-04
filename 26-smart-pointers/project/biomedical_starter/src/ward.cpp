#include "ward.h"

#include <iostream>
#include <utility>

namespace makersplace::clinic {

Ward::Ward(std::string n) : name(n) {}

void Ward::receive(std::unique_ptr<MedicalDevice> device) {
    std::cout << "  " << name << " receives " << device->getSerial() << std::endl;
    devices.push_back(std::move(device));
}

std::unique_ptr<MedicalDevice> Ward::lend(std::string serial) {
    // TODO: find it, std::move it out, erase the slot, return it (or nullptr).
    (void)serial;
    return nullptr;
}

MedicalDevice* Ward::findDevice(std::string serial) {
    for (const std::unique_ptr<MedicalDevice>& d : devices) {
        if (d->getSerial() == serial) {
            return d.get();
        }
    }
    return nullptr;
}

std::shared_ptr<Patient> Ward::admit(std::string folder, std::string patientName) {
    std::shared_ptr<Patient> p = std::make_shared<Patient>(folder, patientName);
    admitted.push_back(p);
    return p;
}

void Ward::discharge(std::string folder) {
    // TODO: remove the patient's shared_ptr from admitted.
    (void)folder;
}

void Ward::printDashboard() const {
    std::cout << name << " dashboard:" << std::endl;
    // TODO: ONE polymorphic loop: each device's status(), its
    // patientDescription(), and "** ATTENTION **" if needsAttention().
}

} // namespace makersplace::clinic
