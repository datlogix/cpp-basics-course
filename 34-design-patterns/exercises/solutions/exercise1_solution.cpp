#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// ---------- Strategy ----------
class BellSchedule {
public:
    virtual ~BellSchedule() = default;
    virtual std::vector<std::string> times() const = 0;
    virtual std::string name() const = 0;
};

class NormalDay : public BellSchedule {
public:
    std::vector<std::string> times() const override {
        return {"08:00", "09:30", "10:00", "11:30", "12:30", "14:00"};
    }
    std::string name() const override { return "normal day"; }
};

class ExamDay : public BellSchedule {
public:
    std::vector<std::string> times() const override { return {"08:30", "11:30", "12:30", "15:30"}; }
    std::string name() const override { return "exam day"; }
};

// ---------- Observer ----------
class BellListener {
public:
    virtual ~BellListener() = default;
    virtual void onBell(const std::string& time) = 0;
};

class ClassroomSpeaker : public BellListener {
private:
    std::string room;

public:
    explicit ClassroomSpeaker(std::string r) : room(r) {}
    void onBell(const std::string& time) override {
        std::cout << "  [speaker " << room << "] RING at " << time << std::endl;
    }
};

class StaffAlert : public BellListener {
public:
    void onBell(const std::string& time) override { std::cout << "  [staff SMS] bell at " << time << std::endl; }
};

class BellLog : public BellListener {
private:
    int bells = 0;

public:
    void onBell(const std::string&) override { bells++; }
    int count() const { return bells; }
};

// ---------- Subject ----------
class SchoolBell {
private:
    const BellSchedule* schedule;
    std::vector<BellListener*> listeners;

public:
    explicit SchoolBell(const BellSchedule& s) : schedule(&s) {}
    void setSchedule(const BellSchedule& s) { schedule = &s; }
    void subscribe(BellListener& l) { listeners.push_back(&l); }
    void unsubscribe(BellListener& l) {
        listeners.erase(std::remove(listeners.begin(), listeners.end(), &l), listeners.end());
    }
    void runDay() {
        std::cout << "Bell schedule: " << schedule->name() << std::endl;
        for (const std::string& t : schedule->times()) {
            for (BellListener* l : listeners) {
                l->onBell(t);
            }
        }
    }
};

// ---------- Factory ----------
std::unique_ptr<BellListener> makeListener(const std::string& type, const std::string& detail) {
    if (type == "speaker") return std::make_unique<ClassroomSpeaker>(detail);
    if (type == "staff") return std::make_unique<StaffAlert>();
    throw std::invalid_argument("unknown listener type: " + type);
}

int main() {
    std::vector<std::pair<std::string, std::string>> config = {
        {"speaker", "JHS 1"}, {"speaker", "Robotics Lab"}, {"staff", ""}, {"projector", "Hall"}};

    NormalDay normal;
    ExamDay exam;
    SchoolBell bell(normal);

    std::vector<std::unique_ptr<BellListener>> listeners; // owns them; the bell only observes
    BellListener* staff = nullptr;
    for (const auto& entry : config) {
        try {
            listeners.push_back(makeListener(entry.first, entry.second));
            bell.subscribe(*listeners.back());
            if (entry.first == "staff") {
                staff = listeners.back().get();
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Config error: " << e.what() << std::endl;
        }
    }
    BellLog log;
    bell.subscribe(log);

    bell.runDay();

    if (staff != nullptr) {
        bell.unsubscribe(*staff);
    }
    bell.setSchedule(exam);
    bell.runDay();

    std::cout << "The log heard " << log.count() << " bells" << std::endl;
    return 0;
}
