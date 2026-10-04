#pragma once

#include <string>

namespace makersplace::energy {

// Owns a raw heap array on purpose, to practise the Rule of Three.
class Waveform {
private:
    std::string label;
    double* samples;
    int count;

public:
    // Fills the waveform with one cycle of a sine wave of the given peak voltage.
    Waveform(std::string l, double peakVolts, int sampleCount);

    // TODO (Part 1): declare the copy constructor
    // TODO (Part 1): declare the copy assignment operator

    ~Waveform();

    void clip(double maxVolts);
    double rms() const;
    void print() const;
};

} // namespace makersplace::energy
