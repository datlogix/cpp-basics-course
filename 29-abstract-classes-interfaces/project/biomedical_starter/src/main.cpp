// VTABLE DIAGRAM (requirement 7): draw the vtable of one concrete class.
//
#include "monitor.h"

#include <iostream>
#include <memory>
#include <vector>

using namespace makersplace::clinic;

void nurseStation(const std::vector<const Alarmable*>& items) {
    std::cout << "Nurse station:" << std::endl;
    for (const Alarmable* a : items) {
        if (a->inAlarm()) {
            std::cout << "  !! " << a->alarmMessage() << std::endl;
        }
    }
}

void printChart(const std::vector<const Chartable*>& items) {
    std::cout << "Observation chart:" << std::endl;
    for (const Chartable* c : items) {
        std::cout << "  " << c->chartEntry() << std::endl;
    }
}

int main() {
    std::vector<std::unique_ptr<VitalSignMonitor>> monitors;
    monitors.push_back(std::make_unique<HeartRateMonitor>("Bed 1", 78));
    monitors.push_back(std::make_unique<HeartRateMonitor>("Bed 2", 152));
    // TODO: add SpO2Monitor and TemperatureMonitor objects

    std::vector<const Alarmable*> alarmables;
    std::vector<const Chartable*> chart;
    for (const auto& m : monitors) {
        m->check();
        alarmables.push_back(m.get());
        chart.push_back(m.get());
    }
    // TODO: add a FluidBalanceRecord to the chart (Chartable, not Alarmable)

    nurseStation(alarmables);
    printChart(chart);

    // TODO (requirement 5): a new patient is admitted to Bed 3. Clone Bed 1's
    // heart-rate monitor configuration, move the clone to "Bed 3", set a
    // new value, check it, and print both chart entries.
    return 0;
}
