#pragma once

#include "medical_device.h"
#include "patient.h"

#include <memory>
#include <string>
#include <vector>

namespace makersplace::clinic {

class Ward {
private:
    std::string name;
    std::vector<std::unique_ptr<MedicalDevice>> devices; // OWNS its devices
    std::vector<std::shared_ptr<Patient>> admitted;      // OWNS (shares) admitted patients

public:
    explicit Ward(std::string n);

    void receive(std::unique_ptr<MedicalDevice> device);
    std::unique_ptr<MedicalDevice> lend(std::string serial); // TODO
    MedicalDevice* findDevice(std::string serial);           // BORROW: may return nullptr

    std::shared_ptr<Patient> admit(std::string folder, std::string patientName);
    void discharge(std::string folder);                      // TODO

    void printDashboard() const;                             // TODO
};

} // namespace makersplace::clinic
