// COMMAND: each request is an OBJECT with execute() and undo(), so
// requests can be queued, logged, and undone.
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// ---- the things being controlled ("receivers") ----
class Light {
private:
    std::string room;
    bool on = false;

public:
    explicit Light(std::string r) : room(r) {}
    void set(bool value) {
        on = value;
        std::cout << "    " << room << " light " << (on ? "ON" : "off") << std::endl;
    }
    bool isOn() const { return on; }
};

class Thermostat {
private:
    double target = 26.0;

public:
    void setTarget(double t) {
        target = t;
        std::cout << "    thermostat set to " << target << " C" << std::endl;
    }
    double getTarget() const { return target; }
};

// ---- commands ----
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string describe() const = 0;
};

class SwitchLight : public Command {
private:
    Light& light;
    bool newValue;
    bool oldValue = false;

public:
    SwitchLight(Light& l, bool v) : light(l), newValue(v) {}
    void execute() override {
        oldValue = light.isOn(); // remember, so we can undo
        light.set(newValue);
    }
    void undo() override { light.set(oldValue); }
    std::string describe() const override { return newValue ? "switch light on" : "switch light off"; }
};

class SetThermostat : public Command {
private:
    Thermostat& thermostat;
    double newTarget;
    double oldTarget = 0;

public:
    SetThermostat(Thermostat& t, double target) : thermostat(t), newTarget(target) {}
    void execute() override {
        oldTarget = thermostat.getTarget();
        thermostat.setTarget(newTarget);
    }
    void undo() override { thermostat.setTarget(oldTarget); }
    std::string describe() const override { return "set thermostat to " + std::to_string(static_cast<int>(newTarget)); }
};

// ---- the invoker: runs commands and keeps a history for undo ----
class RemoteControl {
private:
    std::vector<std::unique_ptr<Command>> history;

public:
    void run(std::unique_ptr<Command> c) {
        std::cout << "  run: " << c->describe() << std::endl;
        c->execute();
        history.push_back(std::move(c));
    }
    void undoLast() {
        if (history.empty()) {
            std::cout << "  nothing to undo" << std::endl;
            return;
        }
        std::cout << "  undo: " << history.back()->describe() << std::endl;
        history.back()->undo();
        history.pop_back();
    }
};

int main() {
    Light lounge("Lounge");
    Thermostat thermostat;
    RemoteControl remote;

    remote.run(std::make_unique<SwitchLight>(lounge, true));
    remote.run(std::make_unique<SetThermostat>(thermostat, 22));
    remote.run(std::make_unique<SetThermostat>(thermostat, 18));

    remote.undoLast(); // back to 22
    remote.undoLast(); // back to 26
    remote.undoLast(); // light off again
    remote.undoLast(); // nothing left
    return 0;
}
