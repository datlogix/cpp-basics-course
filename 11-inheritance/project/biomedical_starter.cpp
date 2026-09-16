// Module 11 Project - Track C: Medical Device Hierarchy
// See project/README.md for requirements.
#include <iostream>
#include <string>

class MedicalDevice {
protected:
    std::string deviceId;
    std::string patientName;

public:
    MedicalDevice(std::string id, std::string patient) : deviceId(id), patientName(patient) {}

    void printHeader() {
        std::cout << "[" << deviceId << "] Patient: " << patientName << std::endl;
    }
};

class Thermometer : public MedicalDevice {
private:
    double temperatureCelsius;

public:
    Thermometer(std::string id, std::string patient, double temp)
        : MedicalDevice(id, patient), temperatureCelsius(temp) {}

    void printReading() {
        printHeader();
        // TODO: print the temperature reading
    }
};

class PulseOximeter : public MedicalDevice {
private:
    int oxygenSaturationPercent;

public:
    PulseOximeter(std::string id, std::string patient, int spo2)
        : MedicalDevice(id, patient), oxygenSaturationPercent(spo2) {}

    void printReading() {
        printHeader();
        // TODO: print the oxygen saturation reading
    }
};

int main() {
    Thermometer t("THERM-01", "Kofi Mensah", 37.2);
    PulseOximeter p("SPO2-01", "Ama Owusu", 98);

    t.printReading();
    p.printReading();

    return 0;
}
