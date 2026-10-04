// Conversion operators - marked explicit so conversions only happen
// when asked for. explicit operator bool still works in conditions.
#include <iostream>
#include <vector>

class Percentage {
private:
    double value; // 0..100

public:
    explicit Percentage(double v) : value(v) {}
    explicit operator double() const { return value / 100.0; } // as a fraction
};

class SensorReading {
private:
    double value;
    bool ok;

public:
    SensorReading(double v, bool valid) : value(v), ok(valid) {}
    explicit operator bool() const { return ok; } // "is this reading usable?"
    double get() const { return value; }
};

int main() {
    Percentage passRate(45);
    double fraction = static_cast<double>(passRate); // explicit: we must ask
    std::cout << "45% as a fraction: " << fraction << std::endl;
    // double oops = passRate;  // ERROR: no silent conversion

    std::vector<SensorReading> readings = {{21.5, true}, {0, false}, {22.1, true}};
    for (const SensorReading& r : readings) {
        if (r) { // explicit operator bool IS allowed in a condition
            std::cout << "reading: " << r.get() << std::endl;
        } else {
            std::cout << "reading: (sensor fault - ignored)" << std::endl;
        }
        // int x = r + 1;  // ERROR: explicit stops this nonsense from compiling
    }
    return 0;
}
