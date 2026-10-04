#pragma once

#include <string>

namespace makersplace::clinic {

// Owns a raw heap array on purpose, to practise the Rule of Three.
class EcgTrace {
private:
    std::string label;
    int* samplesMicrovolts;
    int count;

public:
    EcgTrace(std::string l, const int* source, int n);

    // TODO (Part 1): declare the copy constructor
    // TODO (Part 1): declare the copy assignment operator

    ~EcgTrace();

    void smooth();     // 3-point moving average on the inner samples
    int peak() const;  // largest sample
    void print() const;
};

} // namespace makersplace::clinic
