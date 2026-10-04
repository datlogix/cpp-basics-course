// Templates + inheritance:
//  1. A class TEMPLATE derived from an ordinary abstract base - one
//     template gives many concrete classes, all usable polymorphically.
//  2. A class derived from a template instantiation.
//  3. The this-> rule when the base class depends on T.
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// ---------- 1 ----------
class Channel {
public:
    virtual ~Channel() = default;
    virtual std::string summary() const = 0;
};

template <typename T>
class TypedChannel : public Channel {
private:
    std::string name;
    std::vector<T> samples;

public:
    explicit TypedChannel(std::string n) : name(n) {}
    void record(T value) { samples.push_back(value); }
    std::string summary() const override {
        std::ostringstream out;
        out << name << ": " << samples.size() << " samples, latest "
            << (samples.empty() ? T() : samples.back());
        return out.str();
    }
};

// ---------- 2 ----------
template <typename T>
class Statistics {
protected:
    std::vector<T> values;

public:
    void add(T v) { values.push_back(v); }
    T max() const {
        T best = values.at(0);
        for (const T& v : values) if (v > best) best = v;
        return best;
    }
};

class TemperatureLog : public Statistics<double> { // derived from ONE instantiation
public:
    bool feverDetected() const { return !values.empty() && max() >= 38.0; }
};

// ---------- 3 ----------
template <typename T>
class AlarmedStatistics : public Statistics<T> { // the base DEPENDS on T
private:
    T limit;

public:
    explicit AlarmedStatistics(T l) : limit(l) {}
    void addChecked(T v) {
        this->add(v); // without this->, the compiler won't look in Statistics<T> for add()
        if (v > limit) {
            std::cout << "  ALARM: " << v << " exceeds " << limit << " (" << this->values.size()
                      << " readings so far)" << std::endl;
        }
    }
};

int main() {
    auto voltage = std::make_unique<TypedChannel<double>>("battery voltage");
    auto people = std::make_unique<TypedChannel<int>>("people counter");
    auto door = std::make_unique<TypedChannel<bool>>("door switch");
    voltage->record(12.6);
    voltage->record(12.4);
    people->record(31);
    door->record(true);

    std::vector<std::unique_ptr<Channel>> channels;
    channels.push_back(std::move(voltage));
    channels.push_back(std::move(people));
    channels.push_back(std::move(door));
    for (const auto& c : channels) {
        std::cout << "  " << c->summary() << std::endl; // one loop over three generated classes
    }

    TemperatureLog log;
    log.add(37.2);
    log.add(38.6);
    std::cout << "  fever detected? " << (log.feverDetected() ? "yes" : "no") << std::endl;

    AlarmedStatistics<int> co2(1000);
    for (int ppm : {650, 820, 1150}) {
        co2.addChecked(ppm);
    }
    return 0;
}
