// The same task written twice. The manual version must remember to
// clean up on every exit path - and forgets one. The RAII version
// cannot forget, because cleanup lives in a destructor.
#include <iostream>

class Motor {
public:
    void start() { std::cout << "    motor START" << std::endl; }
    void stop() { std::cout << "    motor STOP" << std::endl; }
};

// --- Manual cleanup: easy to get wrong ---
void driveManual(Motor& m, int batteryPercent) {
    m.start();
    if (batteryPercent < 10) {
        std::cout << "    battery too low, giving up" << std::endl;
        return; // BUG: forgot m.stop() on this path - motor keeps running!
    }
    if (batteryPercent < 30) {
        std::cout << "    short drive only" << std::endl;
        m.stop();
        return;
    }
    std::cout << "    full drive" << std::endl;
    m.stop();
}

// --- RAII: the motor is stopped on EVERY path ---
class MotorSession {
private:
    Motor& motor;

public:
    explicit MotorSession(Motor& m) : motor(m) { motor.start(); }
    ~MotorSession() { motor.stop(); }
};

void driveRaii(Motor& m, int batteryPercent) {
    MotorSession session(m);
    if (batteryPercent < 10) {
        std::cout << "    battery too low, giving up" << std::endl;
        return; // session's destructor stops the motor
    }
    if (batteryPercent < 30) {
        std::cout << "    short drive only" << std::endl;
        return; // ...and here
    }
    std::cout << "    full drive" << std::endl;
} // ...and here

int main() {
    Motor motor;
    int batteryLevels[] = {80, 20, 5};

    std::cout << "Manual version:" << std::endl;
    for (int level : batteryLevels) {
        std::cout << "  battery " << level << "%" << std::endl;
        driveManual(motor, level);
    }

    std::cout << "RAII version:" << std::endl;
    for (int level : batteryLevels) {
        std::cout << "  battery " << level << "%" << std::endl;
        driveRaii(motor, level);
    }
    return 0;
}
