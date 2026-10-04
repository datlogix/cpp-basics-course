// STATIC vs DYNAMIC (requirement 7): which parts use each, and why?
//
#include "column.h"
#include "rolling_window.h"
#include "statistics.h"

#include <iostream>
#include <string>

using namespace makersplace::clinic;

// Two monitor classes that share NO base class.
class PulseMonitor {
private:
    int bpm = 76;

public:
    void update(int b) { bpm = b; }
    int latestValue() const { return bpm; }
    std::string vitalName() const { return "heart rate"; }
};

class ThermometerProbe {
private:
    double celsius = 36.9;

public:
    void update(double c) { celsius = c; }
    double latestValue() const { return celsius; }
    std::string vitalName() const { return "temperature"; }
};

// TODO (requirement 6): concept HasVitalReading, and a constrained
// template <HasVitalReading M> void trend(...)

int main() {
    Statistics<int> heartRates;
    for (int hr : {78, 82, 88, 95, 104, 112}) {
        heartRates.add(hr);
    }
    std::cout << "Heart rate: " << heartRates.count() << " readings, mean " << heartRates.mean()
              << " bpm" << std::endl;

    // TODO: Statistics<bool> alarms; ...fractionInAlarm()
    // TODO: RollingWindow<int, 6> lastHour; forEach to print the trend
    // TODO: an observation chart: ChartColumn<int>, <double>, <bool> in one vector, printed with printTable
    // TODO: trend() with a PulseMonitor AND a ThermometerProbe
    ThermometerProbe probe;
    (void)probe;
    return 0;
}
