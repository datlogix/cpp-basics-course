#pragma once

#include <iostream>

namespace makersplace::clinic {

// A medication dose, stored as whole micrograms (Stage 1 and Stage 3).
// (Simplified for teaching - not for clinical use.)
class Dose {
private:
    long micrograms = 0;

public:
    Dose() = default;
    static Dose mg(double milligrams);
    long inMicrograms() const { return micrograms; }

    Dose& operator+=(const Dose& other);
    // TODO (Stage 3): -=, * (by doses per day), <=>, ==, >> ...

    friend std::ostream& operator<<(std::ostream& os, const Dose& d);
};

Dose operator+(Dose a, const Dose& b);

} // namespace makersplace::clinic
