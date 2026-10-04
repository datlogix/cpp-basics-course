// The order of construction and destruction for members, base classes,
// and local variables. Rule: destruction is ALWAYS the reverse of
// construction.
#include <iostream>
#include <string>

class Part {
private:
    std::string name;

public:
    explicit Part(std::string n) : name(n) { std::cout << "  construct " << name << std::endl; }
    ~Part() { std::cout << "  destroy   " << name << std::endl; }
};

class Machine { // a base class
protected:
    // A default member initializer for a CLASS-type member must use braces
    // { } (parentheses aren't allowed here, because they would look like a
    // function declaration). It means exactly the same as Part("...").
    Part frame{"Machine::frame"};

public:
    Machine() { std::cout << "  Machine constructor body" << std::endl; }
    virtual ~Machine() { std::cout << "  Machine destructor body" << std::endl; }
};

class Robot : public Machine { // a derived class with two members of its own
private:
    Part motor;
    Part camera;

public:
    Robot() : motor("Robot::motor"), camera("Robot::camera") {
        std::cout << "  Robot constructor body (motor and camera already exist)" << std::endl;
    }
    ~Robot() override {
        std::cout << "  Robot destructor body (motor and camera still exist)" << std::endl;
    }
};

int main() {
    std::cout << "Creating a Robot:" << std::endl;
    {
        Robot r;
        std::cout << "Robot in use..." << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Three local Parts:" << std::endl;
    {
        Part first("first");
        Part second("second");
        Part third("third");
    }
    return 0;
}
