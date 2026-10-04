// DECORATOR: add optional behaviour by WRAPPING an object in another
// object with the same interface. Decorators can wrap decorators.
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

class Sensor {
public:
    virtual ~Sensor() = default;
    virtual double read() = 0;
};

class NoisyThermistor : public Sensor { // the plain object
private:
    std::vector<double> samples = {25.0, 27.0, 24.0, 28.0, 26.0, 30.0};
    size_t next = 0;

public:
    double read() override { return samples[next++ % samples.size()]; }
};

class SensorDecorator : public Sensor { // base for all decorators: holds the wrapped sensor
protected:
    std::unique_ptr<Sensor> inner;

public:
    explicit SensorDecorator(std::unique_ptr<Sensor> s) : inner(std::move(s)) {}
};

class Smoothed : public SensorDecorator { // adds: moving average of the last 3 readings
private:
    std::vector<double> recent;

public:
    using SensorDecorator::SensorDecorator;
    double read() override {
        recent.push_back(inner->read());
        if (recent.size() > 3) {
            recent.erase(recent.begin());
        }
        double total = 0;
        for (double r : recent) total += r;
        return total / recent.size();
    }
};

class Calibrated : public SensorDecorator { // adds: an offset correction
private:
    double offset;

public:
    Calibrated(std::unique_ptr<Sensor> s, double o) : SensorDecorator(std::move(s)), offset(o) {}
    double read() override { return inner->read() + offset; }
};

class Logged : public SensorDecorator { // adds: prints every value it passes on
public:
    using SensorDecorator::SensorDecorator;
    double read() override {
        double v = inner->read();
        std::cout << "    [log] " << v << std::endl;
        return v;
    }
};

int main() {
    std::cout << "Plain:" << std::endl;
    NoisyThermistor plain;
    for (int i = 0; i < 3; i++) {
        std::cout << "  " << plain.read() << std::endl;
    }

    std::cout << "Calibrated (-0.5), then smoothed, then logged:" << std::endl;
    std::unique_ptr<Sensor> sensor = std::make_unique<Logged>(
        std::make_unique<Smoothed>(std::make_unique<Calibrated>(std::make_unique<NoisyThermistor>(), -0.5)));
    for (int i = 0; i < 6; i++) {
        sensor->read();
    }
    return 0;
}
