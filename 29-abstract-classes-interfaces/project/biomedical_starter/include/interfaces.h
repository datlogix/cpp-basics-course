#pragma once

#include <string>

namespace makersplace::clinic {

class Alarmable {
public:
    virtual ~Alarmable() = default;
    virtual bool inAlarm() const = 0;
    virtual std::string alarmMessage() const = 0;
};

class Chartable {
public:
    virtual ~Chartable() = default;
    virtual std::string chartEntry() const = 0;
};

} // namespace makersplace::clinic
