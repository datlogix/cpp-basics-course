#include "assessment.h"

#include <iomanip>
#include <sstream>

namespace makersplace::school {

Assessment::Assessment(std::string t) : title(t) {}

double Assessment::percentage() const {
    return 100.0 * rawScore() / maxScore();
}

std::string Assessment::reportLine() const {
    std::ostringstream out;
    out << std::left << std::setw(22) << title << std::right << std::fixed << std::setprecision(1)
        << std::setw(6) << percentage() << "%  (weight " << weight() << ")";
    return out.str();
}

Exam::Exam(std::string t, double m, double total) : Assessment(t), marks(m), outOf(total) {}

std::unique_ptr<Assessment> Exam::clone() const {
    return std::make_unique<Exam>(*this);
}

} // namespace makersplace::school
