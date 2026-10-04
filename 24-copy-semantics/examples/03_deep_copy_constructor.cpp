// A copy constructor that makes a DEEP copy: the new object gets its
// own array. Copies are independent, and both destructors are safe.
// (Copy assignment is still missing - see 04_copy_assignment.cpp.)
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

    // Copy constructor - const reference parameter, allocate NEW memory,
    // copy every value across.
    SampleBuffer(const SampleBuffer& other) : data(new double[other.size]), size(other.size) {
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i]; // other's private members are accessible here
        }
        std::cout << "  (deep copy made)" << std::endl;
    }

    // Copy assignment is forbidden for now - writing it properly is the
    // next example. Rule of Three: destructor, copy constructor, AND this.
    SampleBuffer& operator=(const SampleBuffer&) = delete;

    ~SampleBuffer() {
        delete[] data;
        std::cout << "  (array of " << size << " freed)" << std::endl;
    }

    void set(int index, double value) { data[index] = value; }
    double get(int index) const { return data[index]; }
    const double* address() const { return data; }
};

int main() {
    SampleBuffer a(3);
    a.set(0, 1.5);

    SampleBuffer b = a; // calls our copy constructor

    std::cout << "a's array lives at " << a.address() << std::endl;
    std::cout << "b's array lives at " << b.address() << "  <- different" << std::endl;

    b.set(0, 99.0);
    std::cout << "After b.set(0, 99): a.get(0) = " << a.get(0) << ", b.get(0) = " << b.get(0)
              << std::endl;

    return 0; // two separate arrays, each freed exactly once
}
