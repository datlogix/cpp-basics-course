#include "waveform.h"

#include <cmath>
#include <iostream>

namespace makersplace::energy {

const double PI = 3.14159265358979;

Waveform::Waveform(std::string l, double peakVolts, int sampleCount)
    : label(l), samples(new double[sampleCount]), count(sampleCount) {
    for (int i = 0; i < count; i++) {
        samples[i] = peakVolts * std::sin(2 * PI * i / count);
    }
}

// TODO (Part 1): define the copy constructor (deep copy, print "[copy] ...")
// TODO (Part 1): define the copy assignment operator (print "[assign] ...")

Waveform::~Waveform() {
    std::cout << "  [free] " << label << std::endl;
    delete[] samples;
}

void Waveform::clip(double maxVolts) {
    for (int i = 0; i < count; i++) {
        if (samples[i] > maxVolts) {
            samples[i] = maxVolts;
        } else if (samples[i] < -maxVolts) {
            samples[i] = -maxVolts;
        }
    }
    label += " (clipped)";
}

double Waveform::rms() const {
    double sumSquares = 0;
    for (int i = 0; i < count; i++) {
        sumSquares += samples[i] * samples[i];
    }
    return std::sqrt(sumSquares / count);
}

void Waveform::print() const {
    std::cout << label << ": " << count << " samples, RMS = " << rms() << " V" << std::endl;
}

} // namespace makersplace::energy
