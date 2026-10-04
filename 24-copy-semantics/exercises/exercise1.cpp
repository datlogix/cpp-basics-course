// Exercise 1: Copy Semantics and the Rule of Three
//
// ReadingBuffer (from Module 23's exercise) owns a heap array. Right now
// it has a destructor but NO copy constructor or copy assignment - so it
// breaks the Rule of Three. Copying it would share one array and delete
// it twice.
//
// TODO 1: Write a copy constructor that makes a DEEP copy (its own new
//         array, with the same capacity, count, and values).
// TODO 2: Write a copy assignment operator that:
//           - handles self-assignment,
//           - allocates and fills the new array BEFORE deleting the old one,
//           - returns *this.
// TODO 3: Uncomment the tests in main one block at a time. Each test
//         prints what it expects - check the output matches.
// TODO 4: In a comment under the class, explain in 2-3 sentences how you
//         could have avoided writing TODO 1 and 2 entirely (hint: the Rule
//         of Zero).
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
//
// Bonus: compile with  -fsanitize=address  added. If your Rule of Three
// is wrong, AddressSanitizer reports a "double-free" or "heap-use-after-free"
// error when the program ends. (Module 35 covers sanitizers properly.)
#include <iostream>

class ReadingBuffer {
private:
    double* data;
    int capacity;
    int count = 0;

public:
    explicit ReadingBuffer(int cap) : data(new double[cap]), capacity(cap) {}

    // TODO 1: copy constructor

    // TODO 2: copy assignment operator

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

// TODO 4: your Rule of Zero explanation here

int main() {
    ReadingBuffer original(5);
    original.add(10);
    original.add(20);

    // --- Test 1: copy construction makes an independent copy ---
    // ReadingBuffer copy = original;
    // copy.add(90);
    // std::cout << "original average (expect 15): " << original.average() << std::endl;
    // std::cout << "copy average (expect 40): " << copy.average() << std::endl;

    // --- Test 2: copy assignment replaces existing contents ---
    // ReadingBuffer other(2);
    // other.add(1);
    // other = original;
    // std::cout << "other count (expect 2): " << other.getCount() << std::endl;
    // std::cout << "other average (expect 15): " << other.average() << std::endl;

    // --- Test 3: self-assignment is safe ---
    // other = other;
    // std::cout << "after self-assignment, average (expect 15): " << other.average() << std::endl;

    std::cout << "original average: " << original.average() << std::endl;
    return 0;
}
