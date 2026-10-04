#include "load_monitor.h"

namespace makersplace::energy {

int LoadMonitor::check(const std::vector<Circuit>& circuits) {
    int raised = 0;
    for (const Circuit& c : circuits) {
        if (c.utilisation() > 0.8) {
            alarm.raise(c.getName(), c.utilisation());
            raised++;
        }
    }
    return raised;
}

} // namespace makersplace::energy
