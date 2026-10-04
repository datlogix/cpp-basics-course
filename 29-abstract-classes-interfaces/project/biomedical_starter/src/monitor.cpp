#include "monitor.h"

#include <sstream>

namespace makersplace::clinic {

VitalSignMonitor::VitalSignMonitor(std::string bedLabel, double value)
    : bed(bedLabel), simulatedValue(value) {}

void VitalSignMonitor::check() {
    lastValue = measure();
    lastClass = classify(lastValue);
}

std::string VitalSignMonitor::alarmMessage() const {
    std::ostringstream out;
    out << bed << ": " << vitalName() << " " << lastValue << " " << unit() << " is CRITICAL";
    return out.str();
}

std::string VitalSignMonitor::chartEntry() const {
    std::ostringstream out;
    out << bed << "  " << vitalName() << ": " << lastValue << " " << unit() << " (" << lastClass << ")";
    return out.str();
}

} // namespace makersplace::clinic
