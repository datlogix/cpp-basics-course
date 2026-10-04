// Testing with FAKES. OverheatMonitor depends on two interfaces
// (Module 33's Dependency Inversion), so tests can give it a fake
// thermometer that returns exactly the temperature we want, and a fake
// alarm that records whether it was raised.
#include "minitest.h"

#include <string>
#include <vector>

// ---------- interfaces ----------
class Thermometer {
public:
    virtual ~Thermometer() = default;
    virtual double celsius() const = 0;
};

class Alarm {
public:
    virtual ~Alarm() = default;
    virtual void raise(const std::string& message) = 0;
};

// ---------- the class under test ----------
class OverheatMonitor {
private:
    const Thermometer& thermometer;
    Alarm& alarm;
    double limit;
    int consecutiveHot = 0;

public:
    OverheatMonitor(const Thermometer& t, Alarm& a, double lim) : thermometer(t), alarm(a), limit(lim) {}

    // Raise the alarm only after THREE hot readings in a row (to ignore glitches).
    void check() {
        if (thermometer.celsius() > limit) {
            consecutiveHot++;
            if (consecutiveHot == 3) {
                alarm.raise("overheating");
            }
        } else {
            consecutiveHot = 0;
        }
    }
};

// ---------- fakes ----------
class FakeThermometer : public Thermometer {
public:
    double value = 20.0; // the test sets this directly
    double celsius() const override { return value; }
};

class FakeAlarm : public Alarm {
public:
    std::vector<std::string> raised; // records every call
    void raise(const std::string& message) override { raised.push_back(message); }
};

// ---------- tests ----------
int main() {
    minitest::testCase("normal temperatures never raise the alarm");
    {
        FakeThermometer thermo;
        FakeAlarm alarm;
        OverheatMonitor monitor(thermo, alarm, 30.0);
        thermo.value = 25.0;
        for (int i = 0; i < 10; i++) monitor.check();
        CHECK(alarm.raised.empty());
    }

    minitest::testCase("three hot readings in a row raise the alarm exactly once");
    {
        FakeThermometer thermo;
        FakeAlarm alarm;
        OverheatMonitor monitor(thermo, alarm, 30.0);
        thermo.value = 35.0;
        monitor.check();
        monitor.check();
        CHECK(alarm.raised.empty());
        monitor.check();
        CHECK(alarm.raised.size() == 1);
        monitor.check();
        CHECK(alarm.raised.size() == 1);
    }

    minitest::testCase("a cool reading in between resets the count (a glitch is ignored)");
    {
        FakeThermometer thermo;
        FakeAlarm alarm;
        OverheatMonitor monitor(thermo, alarm, 30.0);
        thermo.value = 35.0;
        monitor.check();
        monitor.check();
        thermo.value = 22.0;
        monitor.check();
        thermo.value = 35.0;
        monitor.check();
        monitor.check();
        CHECK(alarm.raised.empty());
    }

    minitest::testCase("exactly the limit is NOT hot (boundary)");
    {
        FakeThermometer thermo;
        FakeAlarm alarm;
        OverheatMonitor monitor(thermo, alarm, 30.0);
        thermo.value = 30.0;
        for (int i = 0; i < 5; i++) monitor.check();
        CHECK(alarm.raised.empty());
    }

    return TEST_SUMMARY();
}
