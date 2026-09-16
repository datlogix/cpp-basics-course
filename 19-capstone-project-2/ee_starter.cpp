// Capstone 2, Track B: Digital Multimeter & Data Acquisition System
// See README.md for the full staged requirements.
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

const double PI = 3.14159265358979;

// ---------------------------------------------------------------------
// STAGE 3 helper (build this alongside Module 18 if you haven't already)
// ---------------------------------------------------------------------
template <typename T>
class Statistics {
private:
    std::vector<T> values;

public:
    void addValue(T v) { values.push_back(v); }

    double mean() const {
        // TODO
        return 0;
    }

    double standardDeviation() const {
        // TODO
        return 0;
    }
};

// ---------------------------------------------------------------------
// STAGE 1: Component hierarchy
// ---------------------------------------------------------------------
class Component {
protected:
    std::string name;
    double value;

public:
    Component(std::string n, double v) {
        if (v <= 0) {
            throw std::invalid_argument("Component value must be positive.");
        }
        name = n;
        value = v;
    }

    virtual void describe() const {
        std::cout << name << ": " << value << std::endl;
    }

    virtual double impedance(double frequencyHz) const {
        return 0;
    }

    virtual ~Component() {}
};

class Resistor : public Component {
public:
    Resistor(double ohms) : Component("Resistor", ohms) {}
    double impedance(double frequencyHz) const override {
        return value;
    }
};

class Capacitor : public Component {
public:
    Capacitor(double farads) : Component("Capacitor", farads) {}
    double impedance(double frequencyHz) const override {
        // TODO: 1.0 / (2 * PI * frequencyHz * value)
        return 0;
    }
};

class Inductor : public Component {
public:
    Inductor(double henries) : Component("Inductor", henries) {}
    double impedance(double frequencyHz) const override {
        // TODO: 2 * PI * frequencyHz * value
        return 0;
    }
};

int main() {
    const double FREQUENCY_HZ = 60.0;
    const double MAX_SAFE_CURRENT = 5.0;

    std::vector<Component*> circuit;

    // TODO Stage 1: create a Resistor, Capacitor, and Inductor with new,
    // print each one's impedance at FREQUENCY_HZ with one polymorphic loop.

    // TODO Stage 2: log readings to a CSV file (timestamp,node,voltage)
    // with std::ios::app, throw/catch for invalid component values
    // (already partly handled in Component's constructor above) and for
    // an overcurrent condition, and store live samples in a
    // std::map<std::string, std::vector<double>> nodeSamples.

    // TODO Stage 3: use max_element/min_element for peak/lowest voltage
    // per node, count_if for over-voltage events, and feed a node's
    // sample history into a Statistics<double> to flag a "noisy" node.

    for (Component* c : circuit) {
        delete c;
    }

    return 0;
}
