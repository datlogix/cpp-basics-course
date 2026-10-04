#pragma once

#include <string>

namespace makersplace::school {

// OBSERVER (Stage 3): anything that reacts to your system's events
// implements this interface. Add or change events to fit your design.
class SchoolEventListener {
public:
    virtual ~SchoolEventListener() = default;
    virtual void onResultPublished(const std::string& studentId, const std::string& course, double percentage) = 0;
    virtual void onPaymentRecorded(const std::string& studentId, long pesewas) = 0;
};

} // namespace makersplace::school
