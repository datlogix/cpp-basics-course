#include <iostream>

class ReadingBuffer {
private:
    double* data;
    int capacity;
    int count = 0;

public:
    explicit ReadingBuffer(int cap) : data(new double[cap]), capacity(cap) {}

    // Copy constructor: a brand-new array with the same contents.
    ReadingBuffer(const ReadingBuffer& other)
        : data(new double[other.capacity]), capacity(other.capacity), count(other.count) {
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
    }

    // Copy assignment: self-check, copy first, free second, return *this.
    ReadingBuffer& operator=(const ReadingBuffer& other) {
        if (this == &other) {
            return *this;
        }
        double* newData = new double[other.capacity];
        for (int i = 0; i < other.count; i++) {
            newData[i] = other.data[i];
        }
        delete[] data;
        data = newData;
        capacity = other.capacity;
        count = other.count;
        return *this;
    }

    ~ReadingBuffer() { delete[] data; }

    bool add(double value) {
        if (count >= capacity) {
            return false;
        }
        data[count] = value;
        count++;
        return true;
    }

    double average() const {
        if (count == 0) {
            return 0;
        }
        double total = 0;
        for (int i = 0; i < count; i++) {
            total += data[i];
        }
        return total / count;
    }

    int getCount() const { return count; }
};

// Rule of Zero: if data were a std::vector<double> (reserving `capacity`
// elements, or just checking size() against capacity), the compiler-
// generated copy constructor, copy assignment and destructor would all be
// correct, because std::vector deep-copies and frees itself. We would write
// none of the three special member functions.

int main() {
    ReadingBuffer original(5);
    original.add(10);
    original.add(20);

    ReadingBuffer copy = original;
    copy.add(90);
    std::cout << "original average (expect 15): " << original.average() << std::endl;
    std::cout << "copy average (expect 40): " << copy.average() << std::endl;

    ReadingBuffer other(2);
    other.add(1);
    other = original;
    std::cout << "other count (expect 2): " << other.getCount() << std::endl;
    std::cout << "other average (expect 15): " << other.average() << std::endl;

    other = other;
    std::cout << "after self-assignment, average (expect 15): " << other.average() << std::endl;

    std::cout << "original average: " << original.average() << std::endl;
    return 0;
}
