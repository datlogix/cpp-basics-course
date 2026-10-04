#pragma once

#include <string>

namespace makersplace::energy {

class Waveform {
private:
    std::string label;
    double* samples;
    int count;

public:
    static int copies;
    static int moves;

    Waveform(std::string l, double peakVolts, double dcOffset, int sampleCount);
    Waveform(const Waveform& other);
    Waveform& operator=(const Waveform& other);

    // TODO (Part 1): declare the move constructor and move assignment (noexcept)

    ~Waveform();

    void addOffset(double volts);
    void clipTo(double maxVolts);
    void multiply(double gain);
    double mean() const;
    double rms() const;
    int size() const { return count; }
    void print() const;
};

} // namespace makersplace::energy
