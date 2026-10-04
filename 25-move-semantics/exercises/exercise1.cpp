// Exercise 1: Move Semantics and the Rule of Five
//
// ReadingBuffer is Module 24's Rule-of-Three solution, with two static
// counters added so we can COUNT copies and moves.
//
// TODO 1: Add a move constructor: steal other's array, copy capacity and
//         count, leave other EMPTY BUT VALID (data = nullptr, capacity 0,
//         count 0). Mark it noexcept. Increment moveCount.
// TODO 2: Add a move assignment operator: self-check, free our own array,
//         steal other's, leave other empty, return *this. Mark it
//         noexcept. Increment moveCount.
// TODO 3: Run the program BEFORE and AFTER adding TODO 1 and 2, and write
//         both sets of counts in the RESULTS comment below. Explain the
//         difference in one or two sentences.
// TODO 4: Remove "noexcept" from your move constructor only, run again,
//         and record what changes in Test 2. Explain why. Then put
//         noexcept back.
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>
#include <utility>
#include <vector>

class ReadingBuffer {
private:
    double* data;
    int capacity;
    int count = 0;

public:
    static int copyCount;
    static int moveCount;

    explicit ReadingBuffer(int cap) : data(new double[cap]), capacity(cap) {}

    ReadingBuffer(const ReadingBuffer& other)
        : data(new double[other.capacity]), capacity(other.capacity), count(other.count) {
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
        copyCount++;
    }

    ReadingBuffer& operator=(const ReadingBuffer& other) {
        if (this != &other) {
            double* newData = new double[other.capacity];
            for (int i = 0; i < other.count; i++) {
                newData[i] = other.data[i];
            }
            delete[] data;
            data = newData;
            capacity = other.capacity;
            count = other.count;
            copyCount++;
        }
        return *this;
    }

    // TODO 1: move constructor

    // TODO 2: move assignment operator

    ~ReadingBuffer() { delete[] data; }

    bool add(double value) {
        if (count >= capacity) {
            return false;
        }
        data[count] = value;
        count++;
        return true;
    }

    int getCount() const { return count; }
};

int ReadingBuffer::copyCount = 0;
int ReadingBuffer::moveCount = 0;

ReadingBuffer makeFullBuffer(int n) {
    ReadingBuffer b(n);
    for (int i = 0; i < n; i++) {
        b.add(i);
    }
    return b;
}

void report(const char* label) {
    std::cout << label << ": copies = " << ReadingBuffer::copyCount
              << ", moves = " << ReadingBuffer::moveCount << std::endl;
    ReadingBuffer::copyCount = 0;
    ReadingBuffer::moveCount = 0;
}

int main() {
    // Test 1: std::move from a named buffer
    ReadingBuffer week(7);
    week.add(36.6);
    ReadingBuffer archived = std::move(week);
    std::cout << "archived has " << archived.getCount() << ", week has " << week.getCount()
              << std::endl;
    report("Test 1");

    // Test 2: a vector growing as temporaries are pushed in
    std::vector<ReadingBuffer> history;
    for (int i = 0; i < 100; i++) {
        history.push_back(ReadingBuffer(10));
    }
    report("Test 2");

    // Test 3: assigning a returned (temporary) value to an existing buffer
    ReadingBuffer current(1);
    current = makeFullBuffer(500);
    std::cout << "current has " << current.getCount() << std::endl;
    report("Test 3");

    return 0;
}

/*
  RESULTS
    Before TODO 1 and 2:
      Test 1:
      Test 2:
      Test 3:
    After TODO 1 and 2:
      Test 1:
      Test 2:
      Test 3:
    Explanation:

    Without noexcept on the move constructor (TODO 4):
      Test 2:
    Explanation:
*/
