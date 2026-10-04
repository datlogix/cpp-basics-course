// JUDGEMENT TABLE (requirement 7): every operator considered, provided or
// rejected, and why. (Does Dose * Dose mean anything?)
//
//   operator      provided?   reason
//   --------      ---------   ------
//
#pragma once

#include <array>
#include <compare>
#include <iostream>

namespace makersplace::clinic {

class Dose {
private:
    long micrograms = 0;

public:
    Dose() {}
    static Dose mg(double milligrams);
    static Dose mcg(long mcg);

    long inMicrograms() const { return micrograms; }

    Dose& operator+=(const Dose& other);
    // TODO: -=, *= (by int)

    // TODO: <=> and ==

    friend std::ostream& operator<<(std::ostream& os, const Dose& d);
    friend std::istream& operator>>(std::istream& in, Dose& d); // TODO: "500 mg" or "250 mcg"
};

Dose operator+(Dose a, const Dose& b);
// TODO: -, Dose * int, int * Dose

class MedicationChart {
private:
    std::array<Dose, 24> hourly; // one scheduled dose per hour of the day (std::array: a fixed-size array)

public:
    Dose& operator[](int hour);             // TODO: bounds check 0..23
    const Dose& operator[](int hour) const; // TODO: bounds check 0..23
    Dose dailyTotal() const;                // TODO
    const std::array<Dose, 24>& all() const { return hourly; }
};

// TODO: functor ExceedsLimit - holds a maximum single Dose

} // namespace makersplace::clinic
