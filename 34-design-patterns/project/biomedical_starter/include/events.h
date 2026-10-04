#pragma once

#include <string>

namespace makersplace::clinic {

// OBSERVER: anything that wants to hear about vital-sign readings implements this.
class VitalSignListener {
public:
    virtual ~VitalSignListener() = default;
    virtual void onVitalSign(const std::string& bed, const std::string& vital, double value) = 0;
};

// STRATEGY: a way of scoring a vital sign for an early warning score.
// (Simplified for teaching - not for clinical use.)
class ScoringScheme {
public:
    virtual ~ScoringScheme() = default;
    virtual std::string name() const = 0;
    virtual int score(const std::string& vital, double value) const = 0;
};

// COMMAND: an undoable medication administration entry.
class ChartCommand {
public:
    virtual ~ChartCommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string describe() const = 0;
};

} // namespace makersplace::clinic
