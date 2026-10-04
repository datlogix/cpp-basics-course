// NAME HIDING: declaring log() in the derived class hides EVERY log()
// overload in the base class. using Base::log; brings them back.
#include <iostream>
#include <string>

class Logger {
public:
    void log(std::string message) { std::cout << "  [log] " << message << std::endl; }
    void log(int errorCode) { std::cout << "  [log] error code " << errorCode << std::endl; }
};

class HidingLogger : public Logger {
public:
    // Only the string version is redefined...
    void log(std::string message) { std::cout << "  [hiding] " << message << std::endl; }
    // ...so Logger::log(int) is now HIDDEN in HidingLogger.
};

class FixedLogger : public Logger {
public:
    using Logger::log; // bring ALL of Logger's log overloads into this scope
    void log(std::string message) { std::cout << "  [fixed] " << message << std::endl; }
};

int main() {
    HidingLogger h;
    h.log("system started");
    // h.log(404);       // ERROR: no matching function - Logger::log(int) is hidden
    h.Logger::log(404);  // still reachable if you name the base explicitly

    FixedLogger f;
    f.log("system started"); // FixedLogger's own version
    f.log(404);              // Logger::log(int), visible again thanks to using
    return 0;
}
