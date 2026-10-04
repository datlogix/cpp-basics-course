// The DEFAULT copy of a class holding an owning raw pointer copies the
// ADDRESS, not the data: a SHALLOW copy. Both objects share one array.
//
// This example deliberately has NO destructor, so it leaks memory rather
// than crashing. (With a destructor that did delete[] data, the program
// would delete the same array TWICE when a and b die - undefined
// behaviour, typically a crash. Never do this in real code.)
// (Built with -fsanitize=address, LeakSanitizer reports this leak when the
// program ends - that is the demonstration working, not a mistake.)
#include <iostream>

class SampleBuffer {
private:
    double* data;
    int size;

public:
    explicit SampleBuffer(int n) : data(new double[n]), size(n) {
        for (int i = 0; i < size; i++) {
            data[i] = 0.0;
        }
    }

    void set(int index, double value) { data[index] = value; }
    double get(int index) const { return data[index]; }
    const double* address() const { return data; }

    // No copy constructor, no copy assignment, no destructor written:
    // the compiler generates a memberwise copy.
};

int main() {
    SampleBuffer a(3);
    a.set(0, 1.5);

    SampleBuffer b = a; // shallow copy: b.data == a.data

    std::cout << "a's array lives at " << a.address() << std::endl;
    std::cout << "b's array lives at " << b.address() << "  <- the SAME address" << std::endl;

    b.set(0, 99.0); // change b...
    std::cout << "After b.set(0, 99): a.get(0) = " << a.get(0)
              << "  <- a changed too!" << std::endl;

    return 0;
}
