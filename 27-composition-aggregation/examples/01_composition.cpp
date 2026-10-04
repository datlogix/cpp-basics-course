// COMPOSITION: a Robot is made of a Battery and two Motors held BY VALUE.
// The parts are created with the robot and destroyed with it.
// Robot also DELEGATES: batteryLevel() forwards to battery.level().
#include <iostream>
#include <string>

class Battery {
private:
    double chargePercent = 100;

public:
    Battery() { std::cout << "  [+] battery" << std::endl; }
    ~Battery() { std::cout << "  [-] battery" << std::endl; }

    void drain(double amount) {
        chargePercent -= amount;
        if (chargePercent < 0) {
            chargePercent = 0;
        }
    }
    double level() const { return chargePercent; }
};

class Motor {
private:
    std::string side;
    int secondsRun = 0;

public:
    explicit Motor(std::string s) : side(s) { std::cout << "  [+] " << side << " motor" << std::endl; }
    ~Motor() { std::cout << "  [-] " << side << " motor" << std::endl; }

    void run(int seconds) { secondsRun += seconds; }
    int getSecondsRun() const { return secondsRun; }
};

class Robot {
private:
    std::string name;
    Battery battery;   // composition
    Motor leftMotor;   // composition
    Motor rightMotor;  // composition

public:
    explicit Robot(std::string n) : name(n), leftMotor("left"), rightMotor("right") {
        std::cout << "  [+] robot " << name << " (all parts already built)" << std::endl;
    }
    ~Robot() { std::cout << "  [-] robot " << name << " (parts still alive here)" << std::endl; }

    void drive(int seconds) {
        leftMotor.run(seconds);
        rightMotor.run(seconds);
        battery.drain(seconds * 0.5);
    }

    void turnLeft(int seconds) {
        rightMotor.run(seconds); // only one wheel turns
        battery.drain(seconds * 0.25);
    }

    // Delegation: Robot exposes exactly what it chooses to, and the part does the work.
    double batteryLevel() const { return battery.level(); }
};

int main() {
    std::cout << "Building the robot:" << std::endl;
    {
        Robot rover("Kweku");
        rover.drive(30);
        rover.turnLeft(8);
        rover.drive(20);
        std::cout << "  battery now at " << rover.batteryLevel() << "%" << std::endl;
        std::cout << "Robot goes out of scope:" << std::endl;
    }
    return 0;
}
