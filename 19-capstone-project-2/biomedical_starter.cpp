// Capstone 2, Track C: Patient Monitoring & Records System
// See README.md for the full staged requirements.
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// ---------------------------------------------------------------------
// STAGE 3 helper (build this alongside Module 18 if you haven't already)
// ---------------------------------------------------------------------
template <typename T>
class Statistics {
private:
    std::vector<T> values;

public:
    void addValue(T v) { values.push_back(v); }

    double mean() const {
        // TODO
        return 0;
    }

    double standardDeviation() const {
        // TODO
        return 0;
    }
};

// ---------------------------------------------------------------------
// STAGE 2 helper: a value-like class whose constructor enforces safety
// ---------------------------------------------------------------------
class Dosage {
private:
    double milligrams;

public:
    Dosage(double mg) {
        if (mg < 0) {
            throw std::invalid_argument("Dosage cannot be negative.");
        }
        milligrams = mg;
    }

    double getMilligrams() const { return milligrams; }
};

// ---------------------------------------------------------------------
// STAGE 1: MedicalDevice hierarchy
// ---------------------------------------------------------------------
class MedicalDevice {
protected:
    std::string deviceId;
    std::string patientName;

public:
    MedicalDevice(std::string id, std::string patient) : deviceId(id), patientName(patient) {}

    void printHeader() const {
        std::cout << "[" << deviceId << "] Patient: " << patientName << std::endl;
    }

    virtual void printReading() const {
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
    void printReading() const override {
        printHeader();
        std::cout << "  Temperature: " << temperatureCelsius << " C" << std::endl;
    }
};

class PulseOximeter : public MedicalDevice {
private:
    int oxygenSaturationPercent;

public:
    PulseOximeter(std::string id, std::string patient, int spo2)
        : MedicalDevice(id, patient), oxygenSaturationPercent(spo2) {}
    void printReading() const override {
        printHeader();
        std::cout << "  SpO2: " << oxygenSaturationPercent << "%" << std::endl;
    }
};

class ECGMonitor : public MedicalDevice {
private:
    int heartRateBpm;

public:
    ECGMonitor(std::string id, std::string patient, int bpm)
        : MedicalDevice(id, patient), heartRateBpm(bpm) {}
    void printReading() const override {
        printHeader();
        std::cout << "  Heart rate: " << heartRateBpm << " bpm" << std::endl;
    }
};

int main() {
    const double LOW_HEART_RATE = 60.0;
    const double HIGH_HEART_RATE = 100.0;
    const double MAX_SAFE_DOSE_MG = 500.0;

    std::vector<MedicalDevice*> devices;

    // TODO Stage 1: create a Thermometer, PulseOximeter, and ECGMonitor
    // with new, print a unified dashboard with one polymorphic loop.

    // TODO Stage 2: persist every reading to a file
    // (patientId,deviceType,value) with std::ios::app, throw/catch for
    // an out-of-range vital sign and for a Dosage exceeding
    // MAX_SAFE_DOSE_MG, and store each patient's history in a
    // std::map<std::string, std::vector<double>> patientReadings.

    // TODO Stage 3: use count_if to count abnormal readings (outside
    // [LOW_HEART_RATE, HIGH_HEART_RATE] for heart rate, or an
    // appropriate range per vital), use transform to build a risk-score
    // series, and feed a patient's history into a Statistics<double> to
    // flag an "unstable" patient.

    for (MedicalDevice* d : devices) {
        delete d;
    }

    return 0;
}
