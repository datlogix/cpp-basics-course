// OBSERVER: a subject notifies every subscribed observer when something
// happens, without knowing what any of them do.
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class TemperatureObserver {
public:
    virtual ~TemperatureObserver() = default;
    virtual void onTemperature(const std::string& room, double celsius) = 0;
};

class TemperatureSensor { // the SUBJECT
private:
    std::string room;
    std::vector<TemperatureObserver*> observers; // non-owning

public:
    explicit TemperatureSensor(std::string r) : room(r) {}

    void subscribe(TemperatureObserver& o) { observers.push_back(&o); }
    void unsubscribe(TemperatureObserver& o) {
        observers.erase(std::remove(observers.begin(), observers.end(), &o), observers.end());
    }

    void newReading(double celsius) {
        for (TemperatureObserver* o : observers) {
            o->onTemperature(room, celsius);
        }
    }
};

class Display : public TemperatureObserver {
public:
    void onTemperature(const std::string& room, double c) override {
        std::cout << "  [display] " << room << ": " << c << " C" << std::endl;
    }
};

class OverheatAlarm : public TemperatureObserver {
private:
    double limit;

public:
    explicit OverheatAlarm(double l) : limit(l) {}
    void onTemperature(const std::string& room, double c) override {
        if (c > limit) {
            std::cout << "  [ALARM] " << room << " is overheating!" << std::endl;
        }
    }
};

class DailyLog : public TemperatureObserver {
private:
    std::vector<double> readings;

public:
    void onTemperature(const std::string&, double c) override { readings.push_back(c); }
    int count() const { return static_cast<int>(readings.size()); }
};

int main() {
    TemperatureSensor serverRoom("Server room");
    Display display;
    OverheatAlarm alarm(30.0);
    DailyLog log;

    serverRoom.subscribe(display);
    serverRoom.subscribe(alarm);
    serverRoom.subscribe(log);

    serverRoom.newReading(24.5);
    serverRoom.newReading(31.2);

    serverRoom.unsubscribe(display); // the display is switched off
    serverRoom.newReading(33.0);

    std::cout << "  log holds " << log.count() << " readings" << std::endl;
    return 0;
}
