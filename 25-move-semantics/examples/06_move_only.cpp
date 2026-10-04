// A MOVE-ONLY type: copying is deleted (a unique resource can't be
// duplicated) but moving is allowed (it can be handed over).
// std::unique_ptr in Module 26 works exactly like this.
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class SerialPort {
private:
    std::string device; // empty means "not connected"

public:
    explicit SerialPort(std::string dev) : device(dev) {
        std::cout << "  open " << device << std::endl;
    }

    SerialPort(const SerialPort&) = delete;
    SerialPort& operator=(const SerialPort&) = delete;

    SerialPort(SerialPort&& other) noexcept : device(std::move(other.device)) {
        other.device.clear(); // the source no longer owns the connection
    }

    SerialPort& operator=(SerialPort&& other) noexcept {
        if (this != &other) {
            close();
            device = std::move(other.device);
            other.device.clear();
        }
        return *this;
    }

    ~SerialPort() { close(); }

    void close() {
        if (!device.empty()) {
            std::cout << "  close " << device << std::endl;
            device.clear();
        }
    }

    bool isOpen() const { return !device.empty(); }
};

int main() {
    std::vector<SerialPort> ports;

    SerialPort arduino("/dev/ttyUSB0");
    // ports.push_back(arduino);         // ERROR: copy constructor is deleted
    ports.push_back(std::move(arduino)); // OK: ownership handed to the vector

    std::cout << "arduino still open? " << (arduino.isOpen() ? "yes" : "no") << std::endl;
    std::cout << "ports[0] open? " << (ports[0].isOpen() ? "yes" : "no") << std::endl;
    std::cout << "end of main:" << std::endl;
    return 0; // the port is closed exactly once, by the vector's element
}
