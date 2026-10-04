// Composition over inheritance, two ways:
//  1. A SensorLog that inherits from std::vector exposes EVERYTHING and
//     can't protect its rules. One that HAS a vector can.
//  2. A Robot that HAS optional, swappable parts avoids an explosion of
//     subclasses like WheeledRobotWithCameraAndGripper.
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// ---------- 1. Inheriting a container: everything leaks out ----------
class BadSensorLog : public std::vector<double> {
public:
    double average() const {
        double total = 0;
        for (double r : *this) total += r;
        return empty() ? 0 : total / size();
    }
};

// ---------- 1. Composing a container: only what we choose ----------
class SensorLog {
private:
    std::vector<double> readings; // HAS-A vector

public:
    bool add(double celsius) {
        if (celsius < -40 || celsius > 125) { // the rule can't be bypassed
            return false;
        }
        readings.push_back(celsius);
        return true;
    }
    double average() const {
        double total = 0;
        for (double r : readings) total += r;
        return readings.empty() ? 0 : total / readings.size();
    }
    int size() const { return static_cast<int>(readings.size()); } // delegation
};

// ---------- 2. A configurable robot built by composition ----------
class Locomotion { // polymorphic part
public:
    virtual ~Locomotion() {}
    virtual std::string move() const = 0;
};

class Wheels : public Locomotion {
public:
    std::string move() const override { return "rolls forward on wheels"; }
};

class Legs : public Locomotion {
public:
    std::string move() const override { return "walks forward on legs"; }
};

class Camera {
public:
    std::string look() const { return "takes a photo"; }
};

class Gripper {
public:
    std::string grab() const { return "picks up the block"; }
};

class Robot {
private:
    std::string name;
    std::unique_ptr<Locomotion> locomotion;
    std::unique_ptr<Camera> camera;   // nullptr means "no camera"
    std::unique_ptr<Gripper> gripper; // nullptr means "no gripper"

public:
    Robot(std::string n, std::unique_ptr<Locomotion> loco) : name(n), locomotion(std::move(loco)) {}

    void addCamera() { camera = std::make_unique<Camera>(); }
    void addGripper() { gripper = std::make_unique<Gripper>(); }
    void changeLocomotion(std::unique_ptr<Locomotion> loco) { locomotion = std::move(loco); }

    void doMission() const {
        std::cout << "  " << name << " " << locomotion->move();
        if (camera) std::cout << ", " << camera->look();
        if (gripper) std::cout << ", " << gripper->grab();
        std::cout << std::endl;
    }
};

int main() {
    BadSensorLog bad;
    bad.push_back(25.0);
    bad.push_back(9999.0); // nonsense reading accepted - no way to stop it
    bad.clear();           // anyone can wipe the log
    std::cout << "BadSensorLog after clear(): " << bad.size() << " readings" << std::endl;

    SensorLog good;
    good.add(25.0);
    good.add(27.5);
    if (!good.add(9999.0)) {
        std::cout << "SensorLog rejected 9999 C" << std::endl;
    }
    std::cout << "SensorLog average: " << good.average() << " over " << good.size() << " readings"
              << std::endl;
    // good.clear(); // ERROR: SensorLog doesn't offer clear()

    std::cout << "Robots built by composition:" << std::endl;
    Robot scout("Scout", std::make_unique<Wheels>());
    scout.addCamera();

    Robot helper("Helper", std::make_unique<Legs>());
    helper.addCamera();
    helper.addGripper();

    scout.doMission();
    helper.doMission();

    scout.changeLocomotion(std::make_unique<Legs>()); // parts can even change at runtime
    scout.doMission();
    return 0;
}
