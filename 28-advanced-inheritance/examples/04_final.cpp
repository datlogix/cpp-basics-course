// final on a virtual method: no further overriding.
// final on a class: no further deriving.
#include <iostream>
#include <memory>
#include <vector>

class SafetyDevice {
public:
    virtual ~SafetyDevice() {}
    virtual void emergencyStop() = 0;
    virtual void describe() const { std::cout << "  a safety device" << std::endl; }
};

class CircuitBreaker : public SafetyDevice {
public:
    // The emergency-stop behaviour is safety-critical: no subclass may change it.
    void emergencyStop() final { std::cout << "  breaker TRIPPED - power cut" << std::endl; }
    void describe() const override { std::cout << "  a circuit breaker" << std::endl; }
};

class SmartBreaker : public CircuitBreaker {
public:
    // void emergencyStop() override {}  // ERROR: emergencyStop is final in CircuitBreaker
    void describe() const override { std::cout << "  a smart (Wi-Fi) circuit breaker" << std::endl; }
};

// A leaf class: nobody may derive from it.
class ResidualCurrentDevice final : public SafetyDevice {
public:
    void emergencyStop() override { std::cout << "  RCD tripped - earth leakage" << std::endl; }
    void describe() const override { std::cout << "  a residual current device" << std::endl; }
};

// class FancyRcd : public ResidualCurrentDevice {};  // ERROR: ResidualCurrentDevice is final

int main() {
    std::vector<std::unique_ptr<SafetyDevice>> panel;
    panel.push_back(std::make_unique<CircuitBreaker>());
    panel.push_back(std::make_unique<SmartBreaker>());
    panel.push_back(std::make_unique<ResidualCurrentDevice>());

    for (const auto& d : panel) {
        d->describe();
        d->emergencyStop();
    }
    return 0;
}
