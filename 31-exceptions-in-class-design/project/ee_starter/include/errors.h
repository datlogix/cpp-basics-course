#pragma once

#include <stdexcept>
#include <string>

namespace makersplace::energy {

class ElectricalError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class OvercurrentError : public ElectricalError {
private:
    std::string circuit;
    double amps;
    double ratingAmps;

public:
    OvercurrentError(std::string c, double a, double rating)
        : ElectricalError("overcurrent on " + c + ": " + std::to_string(a) + " A exceeds " +
                          std::to_string(rating) + " A breaker"),
          circuit(c), amps(a), ratingAmps(rating) {}
    std::string getCircuit() const { return circuit; }
    double getAmps() const { return amps; }
    double getRating() const { return ratingAmps; }
};

// TODO: OvervoltageError, UnknownCircuitError, CorruptRecordError

} // namespace makersplace::energy
