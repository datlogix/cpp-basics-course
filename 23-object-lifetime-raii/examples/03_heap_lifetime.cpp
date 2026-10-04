// Heap (dynamic) objects survive the end of the function that created
// them. Their destructor runs ONLY when delete is called - and never,
// if delete is forgotten.
// (Built with -fsanitize=address, LeakSanitizer reports this leak when the
// program ends - that is the demonstration working, not a mistake.)
#include <iostream>
#include <string>

class Sensor {
private:
    std::string name;

public:
    explicit Sensor(std::string n) : name(n) {
        std::cout << "  [+] " << name << std::endl;
    }
    ~Sensor() {
        std::cout << "  [-] " << name << std::endl;
    }
};

Sensor* createSensor(std::string name) {
    Sensor* s = new Sensor(name);
    std::cout << "  createSensor returns (the Sensor does NOT die here)" << std::endl;
    return s;
}

int main() {
    Sensor* kept = createSensor("kept sensor");
    Sensor* leaked = createSensor("leaked sensor");

    std::cout << "Back in main, both sensors still exist." << std::endl;

    delete kept; // destructor runs NOW
    std::cout << "kept sensor deleted." << std::endl;

    // We "forget" to delete leaked. Its destructor will NEVER run -
    // notice there is no "[-] leaked sensor" line in the output.
    (void)leaked;

    std::cout << "main ends" << std::endl;
    return 0;
}
