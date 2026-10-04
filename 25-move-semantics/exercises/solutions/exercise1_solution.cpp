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

    ReadingBuffer(ReadingBuffer&& other) noexcept
        : data(other.data), capacity(other.capacity), count(other.count) {
        other.data = nullptr;
        other.capacity = 0;
        other.count = 0;
        moveCount++;
    }

    ReadingBuffer& operator=(ReadingBuffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            capacity = other.capacity;
            count = other.count;
            other.data = nullptr;
            other.capacity = 0;
            other.count = 0;
            moveCount++;
        }
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
  RESULTS (with g++; exact growth counts can differ slightly between compilers)
    Before TODO 1 and 2:
      Test 1: copies = 1, moves = 0   - std::move had no move constructor to choose,
                                        so it fell back to the copy constructor
      Test 2: copies = 227, moves = 0 - 100 pushes copied the temporary in, and
                                        every growth step copied all existing elements
      Test 3: copies = 1, moves = 0   - copy assignment of the temporary
    After TODO 1 and 2:
      Test 1: copies = 0, moves = 1
      Test 2: copies = 0, moves = 227
      Test 3: copies = 0, moves = 1
    Explanation: once move operations exist, every rvalue (temporaries, returned
    values, std::move results) is moved - one pointer handed over - instead of
    having its whole array allocated and copied.

    Without noexcept on the move constructor (TODO 4):
      Test 2: copies = 127, moves = 100
    Explanation: each push_back still MOVES the temporary in, but when the vector
    grows it COPIES its existing elements, because it can't undo a half-finished
    move if one threw an exception. noexcept is the promise it needs.
*/
