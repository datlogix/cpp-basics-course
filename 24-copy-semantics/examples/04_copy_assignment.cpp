// A complete Rule-of-Three class: destructor, copy constructor, and a
// copy assignment operator that handles self-assignment and frees the
// old data AFTER making the new copy.
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

    // 1. Copy constructor
    SampleBuffer(const SampleBuffer& other) : data(new double[other.size]), size(other.size) {
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    // 2. Copy assignment operator
    SampleBuffer& operator=(const SampleBuffer& other) {
        if (this == &other) {
            std::cout << "  (self-assignment - nothing to do)" << std::endl;
            return *this;
        }
        double* newData = new double[other.size]; // copy FIRST
        for (int i = 0; i < other.size; i++) {
            newData[i] = other.data[i];
        }
        delete[] data; // THEN free our old array
        data = newData;
        size = other.size;
        std::cout << "  (assigned: now holds " << size << " samples)" << std::endl;
        return *this;
    }

    // 3. Destructor
    ~SampleBuffer() { delete[] data; }

    void set(int index, double value) { data[index] = value; }
    double get(int index) const { return data[index]; }
    int getSize() const { return size; }
};

int main() {
    SampleBuffer small(2);
    SampleBuffer large(5);
    large.set(4, 7.25);

    small = large;  // small's old 2-element array is freed; it gets a copy of large's
    std::cout << "small now has " << small.getSize() << " samples, last = " << small.get(4)
              << std::endl;

    small = small;  // self-assignment must be safe

    SampleBuffer a(1), b(1), c(3);
    a = b = c;      // works because operator= returns *this
    std::cout << "a has " << a.getSize() << " samples" << std::endl;

    return 0;
}
