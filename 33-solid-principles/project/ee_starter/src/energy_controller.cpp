#include "energy_controller.h"

#include <iomanip>

void EnergyController::add(std::string name, std::string type, double watts, double hours, int priority) {
    ApplianceRecord a;
    a.name = name;
    a.type = type;
    a.watts = watts;
    a.hours = hours;
    a.priority = priority;
    appliances.push_back(a);
}

// Works out energy, prices it, decides load shedding, prints the bill, and sounds alarms.
void EnergyController::runDay(double availableKw) {
    double totalKwh = 0;
    double totalKw = 0;
    std::cout << "DAILY ENERGY REPORT (" << tariffBand << " tariff)" << std::endl;
    for (int i = 0; i < (int)appliances.size(); i++) {
        ApplianceRecord& a = appliances[i];
        double kwh = 0;
        if (a.type == "fridge") {
            kwh = a.watts * 24 * 0.4 / 1000; // compressor runs ~40% of the time
        } else if (a.type == "lighting") {
            kwh = a.watts * a.hours / 1000;
        } else if (a.type == "aircon") {
            kwh = a.watts * a.hours * 0.6 / 1000;
        } else if (a.type == "pump") {
            kwh = a.watts * a.hours / 1000 * 1.1; // motor losses
        }
        totalKwh = totalKwh + kwh;
        totalKw = totalKw + a.watts / 1000;
        std::cout << "  " << std::left << std::setw(16) << a.name << std::right << std::fixed << std::setprecision(2)
                  << kwh << " kWh" << std::endl;
    }

    double cost = 0;
    if (tariffBand == "lifeline") {
        cost = totalKwh * 0.70;
    } else if (tariffBand == "residential") {
        if (totalKwh <= 10) cost = totalKwh * 1.40;
        else cost = 10 * 1.40 + (totalKwh - 10) * 1.85;
    } else if (tariffBand == "commercial") {
        cost = totalKwh * 2.10 + 5.0; // daily service charge
    }
    std::cout << "  total " << totalKwh << " kWh, cost GHS " << cost << std::endl;

    if (totalKw > availableKw) {
        buzzer.beep("demand " + std::to_string((int)(totalKw * 1000)) + " W exceeds supply");
        for (int p = 3; p >= 1 && totalKw > availableKw; p--) {
            for (int i = 0; i < (int)appliances.size(); i++) {
                if (appliances[i].priority == p && totalKw > availableKw) {
                    totalKw = totalKw - appliances[i].watts / 1000;
                    std::cout << "  shedding " << appliances[i].name << std::endl;
                }
            }
        }
    }
    if (cost > 50) {
        buzzer.beep("daily cost above GHS 50");
    }
}
