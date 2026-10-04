// JUDGEMENT TABLE (requirement 7): every operator considered, provided or
// rejected, and why. (Remember: complex numbers have no natural order.)
//
//   operator      provided?   reason
//   --------      ---------   ------
//
#pragma once

#include <iostream>
#include <map>
#include <string>

namespace makersplace::energy {

class Impedance {
private:
    double r; // resistance, ohms
    double x; // reactance, ohms (+ inductive, - capacitive)

public:
    Impedance(double resistance = 0, double reactance = 0) : r(resistance), x(reactance) {}

    double resistance() const { return r; }
    double reactance() const { return x; }
    double magnitude() const;     // TODO: sqrt(r*r + x*x)
    double phaseDegrees() const;  // TODO: atan2(x, r) in degrees

    Impedance& operator+=(const Impedance& o);
    // TODO: -=, *=, /=  (complex multiply and divide)
    // TODO: *= double

    bool operator==(const Impedance& o) const { return r == o.r && x == o.x; }

    friend std::ostream& operator<<(std::ostream& os, const Impedance& z);
    friend std::istream& operator>>(std::istream& in, Impedance& z); // TODO: reads "R X"
};

Impedance operator+(Impedance a, const Impedance& b);
// TODO: -, *, /, Impedance * double, double * Impedance

Impedance parallel(const Impedance& a, const Impedance& b); // TODO: (a * b) / (a + b)

// TODO: functor ByMagnitude - for sorting when needed (no <=> on purpose)

struct ComponentSpec { // a plain bundle of public data
    char type;         // 'R', 'L' or 'C'
    double value;      // ohms, henries or farads
};

class Network {
private:
    std::map<std::string, ComponentSpec> parts;

public:
    ComponentSpec& operator[](const std::string& designator);             // creates if new
    const ComponentSpec& operator[](const std::string& designator) const; // TODO: throw if unknown
};

// TODO: functor ImpedanceAt - holds a frequency; ComponentSpec -> Impedance
//   R: Z = R + j0      L: Z = 0 + j(2*pi*f*L)      C: Z = 0 - j/(2*pi*f*C)

} // namespace makersplace::energy
