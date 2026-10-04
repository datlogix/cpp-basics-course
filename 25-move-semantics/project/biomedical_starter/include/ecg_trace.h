#pragma once

#include <string>

namespace makersplace::clinic {

class EcgTrace {
private:
    std::string label;
    int* samplesMicrovolts;
    int count;

public:
    static int copies;
    static int moves;

    EcgTrace(std::string l, const int* source, int n);
    EcgTrace(const EcgTrace& other);
    EcgTrace& operator=(const EcgTrace& other);

    // TODO (Part 1): declare the move constructor and move assignment (noexcept)

    ~EcgTrace();

    int peak() const;
    int size() const { return count; }
    void print() const;
};

} // namespace makersplace::clinic
