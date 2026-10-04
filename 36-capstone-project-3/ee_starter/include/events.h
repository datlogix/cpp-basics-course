#pragma once

#include <string>

namespace makersplace::energy {

// OBSERVER (Stage 3): anything that reacts to your system's events
// implements this interface. Add or change events to fit your design.
class SensorListener {
public:
    virtual ~SensorListener() = default;
    virtual void onSensorEvent(const std::string& sensorId, const std::string& kind, double value) = 0;
};

} // namespace makersplace::energy
