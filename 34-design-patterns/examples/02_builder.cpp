// BUILDER: construct an object with many optional settings readably,
// with named, chained steps and validation in build().
#include <iostream>
#include <stdexcept>
#include <string>

class Robot {
private:
    std::string name;
    int wheels;
    bool camera;
    bool gripper;
    int batteryMah;
    double maxSpeed;

    friend class RobotBuilder; // only the builder may use the private constructor
    Robot(std::string n, int w, bool c, bool g, int b, double s)
        : name(n), wheels(w), camera(c), gripper(g), batteryMah(b), maxSpeed(s) {}

public:
    void describe() const {
        std::cout << "  " << name << ": " << wheels << " wheels, " << (camera ? "camera, " : "")
                  << (gripper ? "gripper, " : "") << batteryMah << " mAh, max " << maxSpeed << " m/s"
                  << std::endl;
    }
};

class RobotBuilder {
private:
    std::string name;
    int wheelCount = 2;
    bool hasCamera = false;
    bool hasGripper = false;
    int battery = 2000;
    double speed = 0.5;

public:
    explicit RobotBuilder(std::string n) : name(n) {}

    // Each step returns *this, so calls can be chained.
    RobotBuilder& wheels(int n) { wheelCount = n; return *this; }
    RobotBuilder& withCamera() { hasCamera = true; return *this; }
    RobotBuilder& withGripper() { hasGripper = true; return *this; }
    RobotBuilder& batteryCapacity(int mah) { battery = mah; return *this; }
    RobotBuilder& maxSpeed(double ms) { speed = ms; return *this; }

    Robot build() const {
        if (wheelCount != 2 && wheelCount != 4 && wheelCount != 6) {
            throw std::invalid_argument("a robot needs 2, 4 or 6 wheels");
        }
        if (hasGripper && battery < 3000) { // a rule involving TWO settings
            throw std::invalid_argument("a gripper needs at least a 3000 mAh battery");
        }
        return Robot(name, wheelCount, hasCamera, hasGripper, battery, speed);
    }
};

int main() {
    // Compare with: Robot("Scout", 4, true, false, 5000, 1.2) - which bool is which?
    Robot scout = RobotBuilder("Scout").wheels(4).withCamera().batteryCapacity(5000).maxSpeed(1.2).build();
    Robot basic = RobotBuilder("Line follower").build(); // all defaults
    scout.describe();
    basic.describe();

    try {
        Robot bad = RobotBuilder("Lifter").withGripper().build();
        bad.describe();
    } catch (const std::invalid_argument& e) {
        std::cout << "  cannot build: " << e.what() << std::endl;
    }
    return 0;
}
