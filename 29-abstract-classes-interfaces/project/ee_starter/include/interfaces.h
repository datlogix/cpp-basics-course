#pragma once

#include <string>

namespace makersplace::energy {

class Calibratable {
public:
    virtual ~Calibratable() = default;
    virtual void calibrate(double offset) = 0;
};

class Alarmable {
public:
    virtual ~Alarmable() = default;
    virtual bool inAlarm() const = 0;
    virtual std::string alarmMessage() const = 0;
};

} // namespace makersplace::energy
