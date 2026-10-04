// STATIC vs DYNAMIC (requirement 7): which parts use each, and why?
//
#include "column.h"
#include "rolling_window.h"
#include "statistics.h"

#include <iostream>
#include <string>

using namespace makersplace::energy;

// Two sensor classes that share NO base class.
class VoltageProbe {
private:
    mutable int tick = 0;

public:
    double read() const { return 12.0 + 0.3 * ((tick++ % 5) - 2); }
    std::string unit() const { return "V"; }
};

class CurrentClamp {
private:
    mutable int tick = 0;

public:
    double read() const { return 4.5 + 0.1 * (tick++ % 3); }
    std::string unit() const { return "A"; }
};

// TODO (requirement 6): concept Readable, and
// template <Readable S> void sampleInto(const S& sensor, Statistics<double>& stats, int n)

int main() {
    VoltageProbe probe;
    Statistics<double> volts;
    for (int i = 0; i < 10; i++) {
        volts.add(probe.read());
    }
    std::cout << "Battery: " << volts.count() << " samples, mean " << volts.mean() << " V" << std::endl;

    // TODO: Statistics<bool> relay; ...dutyCycle()
    // TODO: RollingWindow<double, 10> for a moving average; forEach to print
    // TODO: a data logger: LogChannel<double>, <int>, <bool> in one vector, printed with printTable
    // TODO: sampleInto() with a VoltageProbe AND a CurrentClamp
    CurrentClamp clamp;
    (void)clamp;
    return 0;
}
