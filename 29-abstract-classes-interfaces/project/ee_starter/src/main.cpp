// VTABLE DIAGRAM (requirement 7): draw the vtable of one concrete class.
//
#include "sensor.h"

#include <iostream>
#include <memory>
#include <vector>

using namespace makersplace::energy;

void alarmPanel(const std::vector<const Alarmable*>& items) {
    std::cout << "Alarm panel:" << std::endl;
    for (const Alarmable* a : items) {
        if (a->inAlarm()) {
            std::cout << "  !! " << a->alarmMessage() << std::endl;
        }
    }
}

void calibrateAll(const std::vector<Calibratable*>& items, double offset) {
    for (Calibratable* c : items) {
        c->calibrate(offset);
    }
}

int main() {
    std::vector<std::unique_ptr<Sensor>> sensors;
    sensors.push_back(std::make_unique<Thermistor>("TH-01", 300));
    sensors.push_back(std::make_unique<Thermistor>("TH-02", 700)); // too hot
    // TODO: add CurrentSensor and LightSensor objects

    std::vector<const Alarmable*> alarmables;
    std::vector<Calibratable*> calibratables;
    for (const auto& s : sensors) {
        Reading r = s->sample();
        std::cout << "  sample: " << r.value << " " << r.unit << (r.valid ? "" : " (INVALID)") << std::endl;
        alarmables.push_back(s.get());
        calibratables.push_back(s.get());
    }
    // TODO: add a tripped CircuitBreaker to alarmables

    alarmPanel(alarmables);
    calibrateAll(calibratables, -0.5);

    // TODO (requirement 5): TH-02 has failed. clone() it onto a replacement
    // with serial "TH-02R", give the replacement a sensible raw value,
    // sample both, and show they are independent.
    return 0;
}
