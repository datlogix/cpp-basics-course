// std::unique_ptr: one owner, automatic delete, move-only.
#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Sensor {
private:
    std::string name;

public:
    explicit Sensor(std::string n) : name(n) { std::cout << "  [+] " << name << std::endl; }
    ~Sensor() { std::cout << "  [-] " << name << std::endl; }
    void read() const { std::cout << "  reading from " << name << std::endl; }
};

int main() {
    std::cout << "1. make_unique:" << std::endl;
    {
        std::unique_ptr<Sensor> s = std::make_unique<Sensor>("thermistor");
        s->read();
        (*s).read();
    } // s destroyed here -> Sensor deleted automatically, no delete written

    std::cout << "2. Moving ownership:" << std::endl;
    std::unique_ptr<Sensor> a = std::make_unique<Sensor>("ultrasonic");
    // std::unique_ptr<Sensor> b = a;          // ERROR: unique_ptr can't be copied
    std::unique_ptr<Sensor> b = std::move(a);  // ownership moves to b
    std::cout << "  a is " << (a ? "full" : "empty") << ", b is " << (b ? "full" : "empty")
              << std::endl;

    std::cout << "3. reset() deletes now:" << std::endl;
    b.reset();
    std::cout << "  b is " << (b ? "full" : "empty") << std::endl;

    std::cout << "4. reset() with a new object replaces the old one:" << std::endl;
    std::unique_ptr<Sensor> c = std::make_unique<Sensor>("light sensor v1");
    c = std::make_unique<Sensor>("light sensor v2"); // v1 deleted, v2 owned

    std::cout << "5. end of main:" << std::endl;
    return 0; // c deleted here
}
