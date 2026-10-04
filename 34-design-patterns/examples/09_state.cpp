// STATE: each mode of an object is a class. Events are passed to the
// current state object, which may switch the object into another state.
#include <iostream>
#include <memory>
#include <string>
#include <utility>

class InfusionPump;

class PumpState {
public:
    virtual ~PumpState() = default;
    virtual std::string name() const = 0;
    virtual void pressStart(InfusionPump& pump) = 0;
    virtual void pressStop(InfusionPump& pump) = 0;
    virtual void occlusionDetected(InfusionPump& pump) = 0;
    virtual void clearAlarm(InfusionPump& pump) = 0;
};

class InfusionPump {
private:
    std::unique_ptr<PumpState> state;

public:
    InfusionPump();
    void setState(std::unique_ptr<PumpState> s) {
        state = std::move(s);
        std::cout << "    -> now " << state->name() << std::endl;
    }
    // Every event is simply delegated to whatever the current state is:
    void pressStart() { state->pressStart(*this); }
    void pressStop() { state->pressStop(*this); }
    void occlusionDetected() { state->occlusionDetected(*this); }
    void clearAlarm() { state->clearAlarm(*this); }
};

class IdleState : public PumpState {
public:
    std::string name() const override { return "IDLE"; }
    void pressStart(InfusionPump& p) override;
    void pressStop(InfusionPump&) override { std::cout << "    (already stopped)" << std::endl; }
    void occlusionDetected(InfusionPump&) override {}
    void clearAlarm(InfusionPump&) override {}
};

class RunningState : public PumpState {
public:
    std::string name() const override { return "RUNNING"; }
    void pressStart(InfusionPump&) override { std::cout << "    (already running)" << std::endl; }
    void pressStop(InfusionPump& p) override { p.setState(std::make_unique<IdleState>()); }
    void occlusionDetected(InfusionPump& p) override;
    void clearAlarm(InfusionPump&) override {}
};

class AlarmState : public PumpState {
public:
    std::string name() const override { return "ALARM (occlusion)"; }
    void pressStart(InfusionPump&) override { std::cout << "    refused: clear the alarm first" << std::endl; }
    void pressStop(InfusionPump&) override { std::cout << "    refused: clear the alarm first" << std::endl; }
    void occlusionDetected(InfusionPump&) override {}
    void clearAlarm(InfusionPump& p) override { p.setState(std::make_unique<IdleState>()); }
};

// Defined after all the state classes exist:
void IdleState::pressStart(InfusionPump& p) { p.setState(std::make_unique<RunningState>()); }
void RunningState::occlusionDetected(InfusionPump& p) { p.setState(std::make_unique<AlarmState>()); }
InfusionPump::InfusionPump() : state(std::make_unique<IdleState>()) {}

int main() {
    InfusionPump pump;
    std::cout << "press stop:" << std::endl;   pump.pressStop();
    std::cout << "press start:" << std::endl;  pump.pressStart();
    std::cout << "press start:" << std::endl;  pump.pressStart();
    std::cout << "occlusion!" << std::endl;    pump.occlusionDetected();
    std::cout << "press start:" << std::endl;  pump.pressStart();
    std::cout << "clear alarm:" << std::endl;  pump.clearAlarm();
    std::cout << "press start:" << std::endl;  pump.pressStart();
    std::cout << "press stop:" << std::endl;   pump.pressStop();
    return 0;
}
