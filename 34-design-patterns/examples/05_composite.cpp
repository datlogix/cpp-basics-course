// COMPOSITE: single items (leaves) and groups (composites) share one
// interface, so a whole tree can be asked the same question as one item.
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class EnergyNode {
public:
    virtual ~EnergyNode() = default;
    virtual std::string name() const = 0;
    virtual double dailyKwh() const = 0;
    virtual void print(int indent) const = 0;
};

class Appliance : public EnergyNode { // a LEAF
private:
    std::string label;
    double watts;
    double hours;

public:
    Appliance(std::string l, double w, double h) : label(l), watts(w), hours(h) {}
    std::string name() const override { return label; }
    double dailyKwh() const override { return watts * hours / 1000.0; }
    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << label << ": " << dailyKwh() << " kWh" << std::endl;
    }
};

class Zone : public EnergyNode { // a COMPOSITE: can hold appliances AND other zones
private:
    std::string label;
    std::vector<std::unique_ptr<EnergyNode>> children;

public:
    explicit Zone(std::string l) : label(l) {}
    Zone& add(std::unique_ptr<EnergyNode> child) {
        children.push_back(std::move(child));
        return *this;
    }
    std::string name() const override { return label; }
    double dailyKwh() const override {
        double total = 0;
        for (const auto& c : children) {
            total += c->dailyKwh(); // works whether c is a leaf or another zone
        }
        return total;
    }
    void print(int indent) const override {
        std::cout << std::string(indent, ' ') << label << " [" << dailyKwh() << " kWh]" << std::endl;
        for (const auto& c : children) {
            c->print(indent + 2);
        }
    }
};

int main() {
    auto kitchen = std::make_unique<Zone>("Kitchen");
    kitchen->add(std::make_unique<Appliance>("Fridge", 150, 24)).add(std::make_unique<Appliance>("Kettle", 2200, 0.5));

    auto lounge = std::make_unique<Zone>("Lounge");
    lounge->add(std::make_unique<Appliance>("TV", 90, 5)).add(std::make_unique<Appliance>("Fan", 75, 8));

    auto groundFloor = std::make_unique<Zone>("Ground floor");
    groundFloor->add(std::move(kitchen)).add(std::move(lounge));

    Zone house("House");
    house.add(std::move(groundFloor)).add(std::make_unique<Appliance>("Borehole pump", 750, 2));

    std::cout << std::fixed << std::setprecision(2);
    house.print(0);
    return 0;
}
