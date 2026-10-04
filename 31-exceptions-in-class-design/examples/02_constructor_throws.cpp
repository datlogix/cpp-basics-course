// When a constructor throws: the object never existed, its destructor
// does NOT run, but members that were already constructed ARE destroyed.
#include <iostream>
#include <stdexcept>
#include <string>

class Part {
private:
    std::string name;

public:
    explicit Part(std::string n) : name(n) { std::cout << "    [+] " << name << std::endl; }
    ~Part() { std::cout << "    [-] " << name << std::endl; }
};

class Patient {
private:
    Part record{"record"};
    Part wristband{"wristband"};
    int age;

public:
    explicit Patient(int a) : age(a) {
        std::cout << "    Patient constructor body" << std::endl;
        if (age < 0 || age > 130) {
            throw std::invalid_argument("invalid age " + std::to_string(age));
        }
    }
    ~Patient() { std::cout << "    ~Patient (destructor body)" << std::endl; }
};

int main() {
    std::cout << "Valid patient:" << std::endl;
    try {
        Patient ok(34);
        std::cout << "    ...in use..." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "    caught: " << e.what() << std::endl;
    }

    std::cout << "Invalid patient:" << std::endl;
    try {
        Patient bad(-3);
        std::cout << "    (never printed)" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "    caught: " << e.what() << std::endl;
    }
    std::cout << "Notice: no '~Patient' line for the invalid one - but both Parts were destroyed."
              << std::endl;
    return 0;
}
