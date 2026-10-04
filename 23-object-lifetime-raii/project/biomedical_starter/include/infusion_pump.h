#pragma once

namespace makersplace::clinic {

// A (simulated) infusion pump. Provided complete - don't change it.
class InfusionPump {
private:
    bool running = false;
    double rateMlPerHour = 0;

public:
    void start(double rate);
    void stop();
    bool isRunning() const { return running; }
};

} // namespace makersplace::clinic
