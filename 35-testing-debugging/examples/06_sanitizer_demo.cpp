// THREE deliberate memory bugs. None of them reliably crashes on its own -
// which is exactly why they're dangerous. AddressSanitizer finds each one
// instantly and says exactly where.
//
// Build WITH sanitizers:
//   g++ -std=c++17 -g -fsanitize=address,undefined 06_sanitizer_demo.cpp -o demo
// Then run one bug at a time:
//   ./demo use-after-free
//   ./demo overflow
//   ./demo leak
//
// Try the same commands on a build WITHOUT -fsanitize: the bugs usually go
// unnoticed, or print nonsense values.
#include <iostream>
#include <string>

class Sensor {
private:
    double lastValue = 21.5;

public:
    double read() const { return lastValue; }
};

void useAfterFree() {
    Sensor* s = new Sensor();
    delete s;
    std::cout << "reading: " << s->read() << std::endl; // BUG: s was already deleted
}

void bufferOverflow() {
    int* readings = new int[5];
    for (int i = 0; i <= 5; i++) { // BUG: <= writes one past the end
        readings[i] = i * 10;
    }
    std::cout << "wrote 6 values into an array of 5" << std::endl;
    delete[] readings;
}

void leak() {
    Sensor* s = new Sensor();
    std::cout << "reading: " << s->read() << std::endl;
    // BUG: no delete. (With a unique_ptr, this bug couldn't happen - Module 26.)
}

int main(int argc, char* argv[]) {
    // argc/argv: the command-line arguments. argv[1] is the first word after the program name.
    if (argc < 2) {
        std::cout << "usage: ./demo use-after-free | overflow | leak" << std::endl;
        return 0;
    }
    std::string which = argv[1];
    if (which == "use-after-free") useAfterFree();
    else if (which == "overflow") bufferOverflow();
    else if (which == "leak") leak();
    else std::cout << "unknown option " << which << std::endl;
    return 0;
}
