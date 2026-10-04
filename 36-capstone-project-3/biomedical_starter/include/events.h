#pragma once

#include <string>

namespace makersplace::clinic {

// OBSERVER (Stage 3): anything that reacts to your system's events
// implements this interface. Add or change events to fit your design.
class VitalSignListener {
public:
    virtual ~VitalSignListener() = default;
    virtual void onVitalSign(const std::string& bed, const std::string& vital, double value) = 0;
};

} // namespace makersplace::clinic
