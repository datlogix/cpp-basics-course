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

// TODO 1: "public" - without it, a class inherits PRIVATELY by default.
// TODO 5: "virtual" so a WeatherStation has only ONE Sensor part.
class TemperatureSensor : virtual public Sensor {
public:
    // TODO 2 would be "using Sensor::Sensor;" - but with a virtual base
    // (TODO 5) we write simple constructors instead.
    explicit TemperatureSensor(std::string n) : Sensor(n) {}

    // TODO 3: declaring calibrate(double, double) here HIDES every
    // Sensor::calibrate overload, so t.calibrate(0.4) found no match.
    // This using-declaration brings the base overloads back.
    using Sensor::calibrate;

    void calibrate(double readingAtZero, double readingAtHundred) {
        offset = -readingAtZero;
        std::cout << "  " << name << ": two-point calibration, span "
                  << (readingAtHundred - readingAtZero) << std::endl;
    }
};

class HumiditySensor : virtual public Sensor {
public:
    explicit HumiditySensor(std::string n) : Sensor(n) {}
    void selfTest() const final { // TODO 4: no further overriding
        std::cout << "  " << name << ": humidity self-test OK" << std::endl;
    }
};

class RainGauge final : public Sensor { // TODO 4: no further deriving
public:
    using Sensor::Sensor;
};

class WeatherStation : public TemperatureSensor, public HumiditySensor {
public:
    // The most-derived class constructs the shared virtual base.
    explicit WeatherStation(std::string n) : Sensor(n), TemperatureSensor(n), HumiditySensor(n) {}
};

void printSensor(const Sensor& s) {
    std::cout << "  sensor: " << s.getName() << std::endl;
}

int main() {
    TemperatureSensor t("Classroom thermometer");
    t.calibrate(0.4);
    t.calibrate(0.3, 99.6);
    std::cout << t.getName() << std::endl;
    printSensor(t);

    HumiditySensor h("Hygrometer");
    h.selfTest();

    RainGauge r("Rain gauge");
    printSensor(r);

    WeatherStation ws("MakersPlace roof station");
    std::cout << "Station name: " << ws.getName() << std::endl;
    printSensor(ws);
    ws.selfTest(); // HumiditySensor's final version overrides Sensor's
    return 0;
}
