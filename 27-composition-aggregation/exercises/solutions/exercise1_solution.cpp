#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

/*
  UML:

  Computer <*>--------- 1 Processor        composition  (value member)
  Computer <*>--------- 1 Memory           composition  (value member)
  Computer <*>--------- 1 Storage          composition  (unique_ptr - polymorphic part)
  Computer <>---------- * Peripheral       aggregation  (non-owning pointers; shared over the day)
  SolidStateDrive ----|> Storage           inheritance
  HardDiskDrive   ----|> Storage           inheritance
  TechnicianReport - - - -> Computer       dependency   (parameter only, never stored)
*/

class Processor {
private:
    double ghz;

public:
    explicit Processor(double speed) : ghz(speed) {}
    ~Processor() { std::cout << "  [-] processor" << std::endl; }
    std::string describe() const { return std::to_string(ghz).substr(0, 3) + " GHz processor"; }
};

class Memory {
private:
    int gigabytes;

public:
    explicit Memory(int gb) : gigabytes(gb) {}
    ~Memory() { std::cout << "  [-] memory" << std::endl; }
    std::string describe() const { return std::to_string(gigabytes) + " GB RAM"; }
};

class Storage {
public:
    virtual ~Storage() { std::cout << "  [-] storage" << std::endl; }
    virtual std::string describe() const = 0;
};

class SolidStateDrive : public Storage {
private:
    int gigabytes;

public:
    explicit SolidStateDrive(int gb) : gigabytes(gb) {}
    std::string describe() const override { return std::to_string(gigabytes) + " GB SSD"; }
};

class HardDiskDrive : public Storage {
private:
    int gigabytes;

public:
    explicit HardDiskDrive(int gb) : gigabytes(gb) {}
    std::string describe() const override { return std::to_string(gigabytes) + " GB HDD"; }
};

class Peripheral {
private:
    std::string name;

public:
    explicit Peripheral(std::string n) : name(n) {}
    ~Peripheral() { std::cout << "  [-] peripheral " << name << std::endl; }
    std::string getName() const { return name; }
};

class Computer {
private:
    std::string labName;
    Processor processor;               // composition (by value)
    Memory memory;                     // composition (by value)
    std::unique_ptr<Storage> storage;  // composition (polymorphic part)
    std::vector<Peripheral*> peripherals; // aggregation (non-owning)

public:
    Computer(std::string name, double ghz, int ramGb, std::unique_ptr<Storage> disk)
        : labName(name), processor(ghz), memory(ramGb), storage(std::move(disk)) {}

    ~Computer() { std::cout << "  [-] computer " << labName << std::endl; }

    void connect(Peripheral& p) { peripherals.push_back(&p); }

    void describe() const { // delegates to each part
        std::cout << labName << ": " << processor.describe() << ", " << memory.describe() << ", "
                  << storage->describe() << std::endl;
        std::cout << "  peripherals:";
        for (const Peripheral* p : peripherals) {
            std::cout << " " << p->getName();
        }
        std::cout << std::endl;
    }
};

class TechnicianReport {
public:
    void print(const Computer& c) const { // dependency: used, never stored
        std::cout << "--- Technician report ---" << std::endl;
        c.describe();
    }
};

int main() {
    Peripheral keyboard("keyboard");
    Peripheral mouse("mouse");
    Peripheral projector("projector");

    TechnicianReport report;
    {
        Computer pc1("ICT-LAB-01", 3.2, 8, std::make_unique<SolidStateDrive>(256));
        Computer pc2("ICT-LAB-02", 2.4, 4, std::make_unique<HardDiskDrive>(500));

        pc1.connect(keyboard);
        pc1.connect(mouse);
        pc2.connect(keyboard); // shared over the day - aggregation allows this
        pc2.connect(projector);

        report.print(pc1);
        report.print(pc2);
        std::cout << "Computers are scrapped:" << std::endl;
    }
    std::cout << "Peripherals still exist: " << keyboard.getName() << ", " << mouse.getName()
              << ", " << projector.getName() << std::endl;
    std::cout << "end of main:" << std::endl;
    return 0;
}
