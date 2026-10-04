#include "waveform.h"

#include <cmath>
#include <iostream>

namespace makersplace::energy {

const double PI = 3.14159265358979;

int Waveform::copies = 0;
int Waveform::moves = 0;

Waveform::Waveform(std::string l, double peakVolts, double dcOffset, int sampleCount)
    : label(l), samples(new double[sampleCount]), count(sampleCount) {
    for (int i = 0; i < count; i++) {
        samples[i] = dcOffset + peakVolts * std::sin(2 * PI * i / count);
    }
}

Waveform::Waveform(const Waveform& other)
    : label(other.label), samples(new double[other.count]), count(other.count) {
    for (int i = 0; i < count; i++) {
        samples[i] = other.samples[i];
    }
    copies++;
}

Waveform& Waveform::operator=(const Waveform& other) {
    if (this != &other) {
        double* newSamples = new double[other.count];
        for (int i = 0; i < other.count; i++) {
            newSamples[i] = other.samples[i];
        }
        delete[] samples;
        samples = newSamples;
        label = other.label;
        count = other.count;
        copies++;
    }
    return *this;
}

// TODO (Part 1): define the move constructor and move assignment here.
// Leave the source with samples == nullptr and count 0, and increment moves.

Waveform::~Waveform() {
    delete[] samples;
}

void Waveform::addOffset(double volts) {
    for (int i = 0; i < count; i++) {
        samples[i] += volts;
    }
}

void Waveform::clipTo(double maxVolts) {
    for (int i = 0; i < count; i++) {
        if (samples[i] > maxVolts) samples[i] = maxVolts;
        if (samples[i] < -maxVolts) samples[i] = -maxVolts;
    }
}

void Waveform::multiply(double gain) {
    for (int i = 0; i < count; i++) {
        samples[i] *= gain;
    }
}

double Waveform::mean() const {
    if (count == 0) return 0;
    double total = 0;
    for (int i = 0; i < count; i++) total += samples[i];
    return total / count;
}

double Waveform::rms() const {
    if (count == 0) return 0;
    double sumSquares = 0;
    for (int i = 0; i < count; i++) sumSquares += samples[i] * samples[i];
    return std::sqrt(sumSquares / count);
}

void Waveform::print() const {
    std::cout << label << ": " << count << " samples, mean " << mean() << " V, RMS " << rms()
              << " V" << std::endl;
}

} // namespace makersplace::energy
