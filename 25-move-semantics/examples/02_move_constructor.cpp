// A full Rule-of-Five class. The output prints array ADDRESSES so you can
// see that a copy creates a new array while a move hands over the same one.
#include <iostream>
#include <utility>

class SampleBuffer {
private:
    double* data;
    int size;

public:
    explicit SampleBuffer(int n) : data(new double[n]), size(n) {
        for (int i = 0; i < size; i++) {
            data[i] = i * 0.5;
        }
    }

    // Copy constructor - deep copy (new array).
    SampleBuffer(const SampleBuffer& other) : data(new double[other.size]), size(other.size) {
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        std::cout << "  COPY constructor: new array at " << data << std::endl;
    }

    // Move constructor - steal the array, leave other empty but valid.
    SampleBuffer(SampleBuffer&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "  MOVE constructor: took array at " << data << std::endl;
    }

    // Copy assignment.
    SampleBuffer& operator=(const SampleBuffer& other) {
        if (this != &other) {
            double* newData = new double[other.size];
            for (int i = 0; i < other.size; i++) {
                newData[i] = other.data[i];
            }
            delete[] data;
            data = newData;
            size = other.size;
            std::cout << "  COPY assignment" << std::endl;
        }
        return *this;
    }

    // Move assignment.
    SampleBuffer& operator=(SampleBuffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "  MOVE assignment" << std::endl;
        }
        return *this;
    }

    ~SampleBuffer() { delete[] data; } // delete[] nullptr is safe - does nothing

    int getSize() const { return size; }
    const double* address() const { return data; }
};

SampleBuffer record(int n) {
    return SampleBuffer(n); // a temporary: built directly in the caller (guaranteed elision)
}

int main() {
    SampleBuffer a(1000);
    std::cout << "a's array is at " << a.address() << std::endl;

    std::cout << "SampleBuffer b = a;" << std::endl;
    SampleBuffer b = a; // a is an lvalue -> copy

    std::cout << "SampleBuffer c = std::move(a);" << std::endl;
    SampleBuffer c = std::move(a); // permission to move -> move
    std::cout << "  a is now empty: size " << a.getSize() << ", array " << a.address() << std::endl;

    std::cout << "b = record(50);" << std::endl;
    b = record(50); // the returned value is an rvalue -> move assignment

    std::cout << "a = c;  (giving the moved-from a a new value is fine)" << std::endl;
    a = c;
    std::cout << "  a has " << a.getSize() << " samples again" << std::endl;
    return 0;
}
