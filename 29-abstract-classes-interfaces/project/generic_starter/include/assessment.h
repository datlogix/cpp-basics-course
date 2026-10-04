#pragma once

#include "interfaces.h"

#include <memory>
#include <string>
#include <vector>

namespace makersplace::school {

class Assessment : public Gradable, public Reportable {
protected:
    std::string title;

    // The steps each kind of assessment must supply:
    virtual double rawScore() const = 0;
    virtual double maxScore() const = 0;

public:
    explicit Assessment(std::string t);

    virtual double weight() const = 0; // e.g. 0.6 for an exam

    // Template Method: the SAME calculation and format for every assessment.
    double percentage() const override;
    std::string reportLine() const override;

    virtual std::unique_ptr<Assessment> clone() const = 0;
};

class Exam : public Assessment {
private:
    double marks;
    double outOf;

protected:
    double rawScore() const override { return marks; }
    double maxScore() const override { return outOf; }

public:
    Exam(std::string t, double m, double total);
    double weight() const override { return 0.6; }
    void setResitMarks(double m) { marks = m; }
    std::unique_ptr<Assessment> clone() const override;
};

// TODO: class Coursework : public Assessment  - average of several assignments (each out of 100)
// TODO: class RoboticsProject : public Assessment - design/build/code/presentation, each out of 25

// TODO: class Attendance : public Reportable  - NOT an Assessment: days present / days in term

} // namespace makersplace::school
