// The Rule of Zero: if every member manages itself, you write NONE of
// the special member functions - and copying is automatically correct.
#include <iostream>
#include <string>
#include <vector>

class SampleBuffer {
private:
    std::string label;
    std::vector<double> data; // std::vector already deep-copies and frees itself

public:
    SampleBuffer(std::string l, int n) : label(l), data(n, 0.0) {}

    void set(int index, double value) { data[index] = value; }
    double get(int index) const { return data[index]; }

    // No destructor. No copy constructor. No copy assignment. Nothing to get wrong.
};

int main() {
    SampleBuffer a("channel A", 3);
    a.set(0, 1.5);

    SampleBuffer b = a; // deep copy, courtesy of std::vector
    b.set(0, 99.0);

    std::cout << "a.get(0) = " << a.get(0) << ", b.get(0) = " << b.get(0) << std::endl;

    SampleBuffer c("channel C", 10);
    c = a; // correct assignment, also free
    std::cout << "c.get(0) = " << c.get(0) << std::endl;
    return 0;
}
