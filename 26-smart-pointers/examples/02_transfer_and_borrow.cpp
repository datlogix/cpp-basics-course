// Function signatures that SAY what happens to ownership:
//   returning unique_ptr     -> "I made this; it's yours now"
//   taking unique_ptr        -> "give it to me; I own it now"
//   taking T& / const T*     -> "let me borrow it; you still own it"
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Sensor {
private:
    std::string name;
    double offset = 0;

public:
    explicit Sensor(std::string n) : name(n) {}
    ~Sensor() { std::cout << "  [-] " << name << " deleted" << std::endl; }

    void setOffset(double o) { offset = o; }
    std::string getName() const { return name; }
    double getOffset() const { return offset; }
};

// A factory: creates, and transfers ownership to the caller.
std::unique_ptr<Sensor> createSensor(std::string name) {
    return std::make_unique<Sensor>(name);
}

class Robot {
private:
    std::vector<std::unique_ptr<Sensor>> sensors;

public:
    // TAKES ownership.
    void install(std::unique_ptr<Sensor> sensor) {
        std::cout << "  robot now owns " << sensor->getName() << std::endl;
        sensors.push_back(std::move(sensor));
    }

    // Lends out a non-owning pointer (nullptr if not found).
    Sensor* find(std::string name) {
        for (const std::unique_ptr<Sensor>& s : sensors) {
            if (s->getName() == name) {
                return s.get();
            }
        }
        return nullptr;
    }
};

// BORROWS: a sensor is required.
void calibrate(Sensor& sensor, double offset) {
    sensor.setOffset(offset);
}

// BORROWS: a sensor may be absent.
void printIfPresent(const Sensor* sensor) {
    if (sensor == nullptr) {
        std::cout << "  (no such sensor)" << std::endl;
        return;
    }
    std::cout << "  " << sensor->getName() << " offset " << sensor->getOffset() << std::endl;
}

int main() {
    Robot robot;

    std::unique_ptr<Sensor> left = createSensor("left IR sensor");
    calibrate(*left, 0.25);              // borrow: left still owns it
    robot.install(std::move(left));      // transfer: robot owns it now
    std::cout << "  left is now " << (left ? "full" : "empty") << std::endl;

    robot.install(createSensor("right IR sensor"));  // a temporary moves automatically

    printIfPresent(robot.find("left IR sensor"));
    printIfPresent(robot.find("camera"));

    std::cout << "end of main - the robot deletes its sensors:" << std::endl;
    return 0;
}
