#include "load_monitor.h"

#include <iostream>

using namespace makersplace::energy;

class ConsoleAlarm : public Alarm {
public:
    void raise(const std::string& circuit, double utilisation) override {
        std::cout << "  [ALARM] " << circuit << " at " << utilisation * 100 << "% of rating" << std::endl;
    }
};

int main() {
    Circuit kitchen("Kitchen", 20);
    kitchen.addLoad("Kettle", 2200);
    kitchen.addLoad("Microwave", 1100);
    kitchen.addLoad("Fridge", 150);
    std::cout << "Kitchen draws " << kitchen.totalAmps() << " A" << std::endl;

    ConsoleAlarm alarm;
    LoadMonitor monitor(alarm);
    monitor.check({kitchen});
    return 0;
}
