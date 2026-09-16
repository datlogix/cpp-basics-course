// Module 12 Project - Track C: Unified Patient Monitor
// See project/README.md for requirements.
#include <iostream>
#include <string>
#include <vector>

class MedicalDevice {
protected:
    std::string deviceId;
    std::string patientName;

public:
    MedicalDevice(std::string id, std::string patient) : deviceId(id), patientName(patient) {}
    void printHeader() {
        std::cout << "[" << deviceId << "] Patient: " << patientName << std::endl;
    }
    virtual void printReading() {
        printHeader();
        std::cout << "  (no reading available)" << std::endl;
    }
    virtual ~MedicalDevice() {}
};

class Thermometer : public MedicalDevice {
private:
    double temperatureCelsius;

public:
    Thermometer(std::string id, std::string patient, double temp)
        : MedicalDevice(id, patient), temperatureCelsius(temp) {}
    void printReading() override {
        printHeader();
        // TODO: print the temperature reading, indented
    }
};

class PulseOximeter : public MedicalDevice {
private:
    int oxygenSaturationPercent;

public:
    PulseOximeter(std::string id, std::string patient, int spo2)
        : MedicalDevice(id, patient), oxygenSaturationPercent(spo2) {}
    void printReading() override {
        printHeader();
        // TODO: print the SpO2 reading, indented
    }
};

class ECGMonitor : public MedicalDevice {
private:
    int heartRateBpm;

public:
    ECGMonitor(std::string id, std::string patient, int bpm)
        : MedicalDevice(id, patient), heartRateBpm(bpm) {}
    void printReading() override {
        printHeader();
        // TODO: print the heart rate reading, indented
    }
};

int main() {
    std::vector<MedicalDevice*> devices;
    devices.push_back(new Thermometer("THERM-01", "Kofi Mensah", 37.2));
    devices.push_back(new PulseOximeter("SPO2-01", "Ama Owusu", 98));
    devices.push_back(new ECGMonitor("ECG-01", "Yaw Boateng", 72));

    // TODO: loop over devices, calling printReading() on each - one loop,
    // three different device types, correctly handled.

    // TODO: delete every pointer in devices.

    return 0;
}
