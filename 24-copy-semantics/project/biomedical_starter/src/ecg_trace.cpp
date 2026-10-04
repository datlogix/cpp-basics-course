#include "ecg_trace.h"

#include <iostream>

namespace makersplace::clinic {

EcgTrace::EcgTrace(std::string l, const int* source, int n)
    : label(l), samplesMicrovolts(new int[n]), count(n) {
    for (int i = 0; i < count; i++) {
        samplesMicrovolts[i] = source[i];
    }
}

// TODO (Part 1): define the copy constructor (deep copy, print "[copy] ...")
// TODO (Part 1): define the copy assignment operator (print "[assign] ...")

EcgTrace::~EcgTrace() {
    std::cout << "  [free] " << label << std::endl;
    delete[] samplesMicrovolts;
}

void EcgTrace::smooth() {
    if (count < 3) {
        return;
    }
    int* smoothed = new int[count];
    smoothed[0] = samplesMicrovolts[0];
    smoothed[count - 1] = samplesMicrovolts[count - 1];
    for (int i = 1; i < count - 1; i++) {
        smoothed[i] = (samplesMicrovolts[i - 1] + samplesMicrovolts[i] + samplesMicrovolts[i + 1]) / 3;
    }
    delete[] samplesMicrovolts;
    samplesMicrovolts = smoothed;
    label += " (smoothed)";
}

int EcgTrace::peak() const {
    int best = samplesMicrovolts[0];
    for (int i = 1; i < count; i++) {
        if (samplesMicrovolts[i] > best) {
            best = samplesMicrovolts[i];
        }
    }
    return best;
}

void EcgTrace::print() const {
    std::cout << label << ": " << count << " samples, peak " << peak() << " uV" << std::endl;
}

} // namespace makersplace::clinic
