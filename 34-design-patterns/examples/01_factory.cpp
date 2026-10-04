// FACTORY: one place decides which concrete class to create from runtime
// data. The rest of the program only ever sees the base class.
// Shown twice: a simple factory function, and an extensible registry.
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

class Sensor {
protected:
    std::string id;

public:
    explicit Sensor(std::string i) : id(i) {}
    virtual ~Sensor() = default;
    virtual std::string describe() const = 0;
};

class Thermistor : public Sensor {
public:
    using Sensor::Sensor;
    std::string describe() const override { return id + ": thermistor (C)"; }
};

class LightSensor : public Sensor {
public:
    using Sensor::Sensor;
    std::string describe() const override { return id + ": light sensor (lux)"; }
};

class GasSensor : public Sensor {
public:
    using Sensor::Sensor;
    std::string describe() const override { return id + ": gas sensor (ppm)"; }
};

// ---- 1. A simple factory function: the ONLY place concrete classes are named ----
std::unique_ptr<Sensor> makeSensor(const std::string& type, const std::string& id) {
    if (type == "temperature") return std::make_unique<Thermistor>(id);
    if (type == "light") return std::make_unique<LightSensor>(id);
    if (type == "gas") return std::make_unique<GasSensor>(id);
    throw std::invalid_argument("unknown sensor type: " + type);
}

// ---- 2. A registry-based factory: new types REGISTER, nothing is edited ----
class SensorFactory {
private:
    // std::function can hold any callable - here, a lambda that creates a sensor.
    std::map<std::string, std::function<std::unique_ptr<Sensor>(const std::string&)>> creators;

public:
    template <typename T>
    void registerType(const std::string& type) {
        creators[type] = [](const std::string& id) { return std::make_unique<T>(id); };
    }

    std::unique_ptr<Sensor> create(const std::string& type, const std::string& id) const {
        auto it = creators.find(type);
        if (it == creators.end()) {
            throw std::invalid_argument("unknown sensor type: " + type);
        }
        return it->second(id);
    }
};

int main() {
    // A configuration file, as text: "type id" per line.
    std::istringstream config("temperature T1\nlight L1\ngas G1\nhumidity H1\n");

    std::vector<std::unique_ptr<Sensor>> sensors;
    std::string type, id;
    while (config >> type >> id) {
        try {
            sensors.push_back(makeSensor(type, id));
        } catch (const std::invalid_argument& e) {
            std::cout << "skipped: " << e.what() << std::endl;
        }
    }
    for (const auto& s : sensors) {
        std::cout << "  " << s->describe() << std::endl;
    }

    SensorFactory factory;
    factory.registerType<Thermistor>("temperature");
    factory.registerType<GasSensor>("gas");
    std::cout << "  " << factory.create("gas", "G2")->describe() << " (from the registry)" << std::endl;
    return 0;
}
