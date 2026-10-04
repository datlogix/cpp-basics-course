#pragma once

#include <string>

namespace makersplace::school {

// OBSERVER: anything that wants to hear about school events implements this.
class SchoolEventListener {
public:
    virtual ~SchoolEventListener() = default;
    virtual void onResultPublished(const std::string& studentId, const std::string& subject, double percentage) = 0;
    virtual void onFeePaid(const std::string& studentId, double amountGhs) = 0;
};

// STRATEGY: a way of turning a percentage into a grade.
class GradingScheme {
public:
    virtual ~GradingScheme() = default;
    virtual std::string name() const = 0;
    virtual std::string grade(double percentage) const = 0;
};

// COMMAND: an undoable gradebook edit.
class GradebookCommand {
public:
    virtual ~GradebookCommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string describe() const = 0;
};

} // namespace makersplace::school
