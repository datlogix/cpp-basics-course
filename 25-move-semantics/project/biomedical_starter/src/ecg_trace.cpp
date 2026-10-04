#include "ecg_trace.h"

#include <iostream>

namespace makersplace::clinic {

int EcgTrace::copies = 0;
int EcgTrace::moves = 0;

EcgTrace::EcgTrace(std::string l, const int* source, int n)
    : label(l), samplesMicrovolts(new int[n]), count(n) {
    for (int i = 0; i < count; i++) {
        samplesMicrovolts[i] = source[i];
    }
}

EcgTrace::EcgTrace(const EcgTrace& other)
    : label(other.label), samplesMicrovolts(new int[other.count]), count(other.count) {
    for (int i = 0; i < count; i++) {
        samplesMicrovolts[i] = other.samplesMicrovolts[i];
    }
    copies++;
}

EcgTrace& EcgTrace::operator=(const EcgTrace& other) {
    if (this != &other) {
        int* newSamples = new int[other.count];
        for (int i = 0; i < other.count; i++) {
            newSamples[i] = other.samplesMicrovolts[i];
        }
        delete[] samplesMicrovolts;
        samplesMicrovolts = newSamples;
        label = other.label;
        count = other.count;
        copies++;
    }
    return *this;
}

// TODO (Part 1): define the move constructor and move assignment here.
// Leave the source with samplesMicrovolts == nullptr and count 0, and
// increment moves.

EcgTrace::~EcgTrace() {
    delete[] samplesMicrovolts;
}

int EcgTrace::peak() const {
    if (count == 0) {
        return 0;
    }
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
