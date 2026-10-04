// A non-type template parameter: the capacity is part of the TYPE.
// RingBuffer<T, N> keeps only the most recent N values - no heap memory.
#include <iostream>
#include <string>

template <typename T, int Capacity>
class RingBuffer {
private:
    T data[Capacity]; // a plain array: its size is known at compile time
    int start = 0;    // index of the oldest value
    int count = 0;

public:
    void push(const T& value) {
        if (count < Capacity) {
            data[(start + count) % Capacity] = value;
            count++;
        } else {
            data[start] = value;            // overwrite the oldest
            start = (start + 1) % Capacity;
        }
    }

    int size() const { return count; }
    int capacity() const { return Capacity; }

    // i = 0 is the oldest value still kept
    const T& operator[](int i) const { return data[(start + i) % Capacity]; }

    void print(const std::string& label) const {
        std::cout << label << " (" << count << "/" << Capacity << "):";
        for (int i = 0; i < count; i++) {
            std::cout << " " << (*this)[i];
        }
        std::cout << std::endl;
    }
};

int main() {
    RingBuffer<double, 4> lastFour;
    for (double t : {36.5, 36.7, 37.1, 37.9, 38.4, 38.2}) {
        lastFour.push(t);
        lastFour.print("temps");
    }

    RingBuffer<int, 3> lastThreeCounts;
    for (int c = 1; c <= 5; c++) {
        lastThreeCounts.push(c * 10);
    }
    lastThreeCounts.print("counts");

    // lastFour = lastThreeCounts;  // ERROR: different types entirely

    const int WINDOW = 2;            // a compile-time constant is fine
    RingBuffer<std::string, WINDOW> lastTwoEvents;
    lastTwoEvents.push("door opened");
    lastTwoEvents.push("motion detected");
    lastTwoEvents.push("lights on");
    lastTwoEvents.print("events");
    return 0;
}
