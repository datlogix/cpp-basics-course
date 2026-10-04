// Exercise 1: Advanced Inheritance
//
// This program is meant to model a school weather station. It does NOT
// compile yet. Fix it step by step - after each TODO, compile again and
// read the next error.
//
// TODO 1: TemperatureSensor is supposed to be a Sensor (is-a), but main
//         can't call getName() on it or pass it to printSensor(). Fix
//         the inheritance mode.
// TODO 2: TemperatureSensor's two constructors only forward to Sensor's.
//         Replace them with ONE line that inherits Sensor's constructors.
// TODO 3: TemperatureSensor adds calibrate(double, double), and now
//         main's call to the base's calibrate(double) fails to compile.
//         Explain WHY in a comment, then fix it with one line.
// TODO 4: HumiditySensor's selfTest() must never be overridden further,
//         and nobody should ever derive from RainGauge. Enforce both.
// TODO 5: WeatherStation inherits from BOTH TemperatureSensor and
//         HumiditySensor, so it contains TWO Sensor parts (two names!)
//         and getName() is ambiguous. Use virtual inheritance so there is
//         exactly ONE Sensor, and give WeatherStation a constructor that
//         constructs it. (Hint: for this step it's simplest to give
//         TemperatureSensor and HumiditySensor ordinary one-argument
//         constructors again, instead of inherited ones.)
// TODO 6: Uncomment the WeatherStation lines in main and check the output
//         shows ONE name.
//
// Compile and run:
//   g++ -std=c++17 -Wall -Wextra exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>
#include <string>

class Sensor {
protected:
    std::string name;
    double offset = 0;

public:
    Sensor(std::string n, double initialOffset) : name(n), offset(initialOffset) {}
    explicit Sensor(std::string n) : Sensor(n, 0.0) {}
    virtual ~Sensor() {}

    std::string getName() const { return name; }
    void calibrate(double newOffset) { offset = newOffset; }
    virtual void selfTest() const { std::cout << "  " << name << ": basic self-test OK" << std::endl; }
};

class TemperatureSensor : Sensor { // TODO 1
public:
    TemperatureSensor(std::string n, double o) : Sensor(n, o) {} // TODO 2
    explicit TemperatureSensor(std::string n) : Sensor(n) {}     // TODO 2

    // Two-point calibration: ice point and boiling point readings.
    void calibrate(double readingAtZero, double readingAtHundred) { // TODO 3
        offset = -readingAtZero;
        std::cout << "  " << name << ": two-point calibration, span "
                  << (readingAtHundred - readingAtZero) << std::endl;
    }
};

class HumiditySensor : public Sensor {
public:
    using Sensor::Sensor;
    void selfTest() const override { // TODO 4
        std::cout << "  " << name << ": humidity self-test OK" << std::endl;
    }
};

class RainGauge : public Sensor { // TODO 4
public:
    using Sensor::Sensor;
};

class WeatherStation : public TemperatureSensor, public HumiditySensor { // TODO 5
public:
    // TODO 5: a constructor taking the station's name
};

void printSensor(const Sensor& s) {
    std::cout << "  sensor: " << s.getName() << std::endl;
}

int main() {
    TemperatureSensor t("Classroom thermometer");
    t.calibrate(0.4);        // base version
    t.calibrate(0.3, 99.6);  // TemperatureSensor's version
    std::cout << t.getName() << std::endl;
    printSensor(t);

    HumiditySensor h("Hygrometer");
    h.selfTest();

    RainGauge r("Rain gauge");
    printSensor(r);

    // TODO 6:
    // WeatherStation ws("MakersPlace roof station");
    // std::cout << "Station name: " << ws.getName() << std::endl;
    // printSensor(ws);
    return 0;
}
