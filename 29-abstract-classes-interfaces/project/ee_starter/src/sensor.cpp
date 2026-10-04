#include "sensor.h"

#include <sstream>

namespace makersplace::energy {

Sensor::Sensor(std::string s, int raw) : serial(s), simulatedRaw(raw) {}

Reading Sensor::sample() {
    double value = convert(readRaw()) + offset;
    last = Reading{value, unit(), inRange(value)};
    return last;
}

std::string Sensor::alarmMessage() const {
    std::ostringstream out;
    out << serial << " out of range: " << last.value << " " << last.unit;
    return out.str();
}

} // namespace makersplace::energy
