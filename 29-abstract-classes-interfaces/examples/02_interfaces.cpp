// Interfaces: classes with ONLY pure virtual functions and no data.
// A class can implement several. Functions that depend only on an
// interface work with any class that implements it.
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Printable {
public:
    virtual ~Printable() = default;
    virtual void print() const = 0;
};

class Saveable {
public:
    virtual ~Saveable() = default;
    virtual std::string toCsv() const = 0;
};

// Implements BOTH interfaces.
class StudentRecord : public Printable, public Saveable {
private:
    std::string name;
    double average;

public:
    StudentRecord(std::string n, double avg) : name(n), average(avg) {}
    void print() const override { std::cout << "  Student " << name << ", average " << average << std::endl; }
    std::string toCsv() const override {
        std::ostringstream out;
        out << "student," << name << "," << average;
        return out.str();
    }
};

// Implements only Saveable.
class SensorReading : public Saveable {
private:
    std::string sensor;
    double value;

public:
    SensorReading(std::string s, double v) : sensor(s), value(v) {}
    std::string toCsv() const override {
        std::ostringstream out;
        out << "reading," << sensor << "," << value;
        return out.str();
    }
};

// Implements only Printable.
class Announcement : public Printable {
private:
    std::string text;

public:
    explicit Announcement(std::string t) : text(t) {}
    void print() const override { std::cout << "  NOTICE: " << text << std::endl; }
};

// These functions depend ONLY on the interfaces - not on any concrete class.
void printAll(const std::vector<const Printable*>& items) {
    for (const Printable* p : items) {
        p->print();
    }
}

void saveAll(const std::vector<const Saveable*>& items, std::string filename) {
    std::ofstream file(filename);
    for (const Saveable* s : items) {
        file << s->toCsv() << "\n";
    }
    std::cout << "  saved " << items.size() << " records to " << filename << std::endl;
}

int main() {
    StudentRecord ama("Ama", 82.5);
    StudentRecord kojo("Kojo", 74.0);
    SensorReading temp("lab-temp", 28.4);
    Announcement notice("Robotics club meets on Saturday at 10am");

    std::cout << "Printing:" << std::endl;
    printAll({&ama, &kojo, &notice});

    std::cout << "Saving:" << std::endl;
    saveAll({&ama, &kojo, &temp}, "records.csv");

    std::ifstream in("records.csv");
    std::string line;
    while (std::getline(in, line)) {
        std::cout << "  file: " << line << std::endl;
    }
    return 0;
}
