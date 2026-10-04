// Tracing: print from the constructor and destructor to SEE exactly
// when each object is born and dies. Predict the output before running!
#include <iostream>
#include <string>

class Sensor {
private:
    std::string name;

public:
    explicit Sensor(std::string n) : name(n) {
        std::cout << "  [+] Sensor " << name << " switched on" << std::endl;
    }

    ~Sensor() {
        std::cout << "  [-] Sensor " << name << " switched off" << std::endl;
    }
};

void takeReading() {
    std::cout << " takeReading() starts" << std::endl;
    Sensor local("C");
    std::cout << " takeReading() ends" << std::endl;
} // local dies here

int main() {
    std::cout << "main starts" << std::endl;
    Sensor a("A");

    {
        std::cout << " inner block starts" << std::endl;
        Sensor b("B");
        std::cout << " inner block ends" << std::endl;
    } // b dies here

    takeReading();

    std::cout << "A temporary:" << std::endl;
    Sensor("Temp"); // a temporary: dies at the end of this statement
    std::cout << "after the temporary" << std::endl;

    std::cout << "main ends" << std::endl;
    return 0;
} // a dies here
