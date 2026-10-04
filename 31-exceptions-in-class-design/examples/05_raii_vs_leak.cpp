// With raw new/delete, an exception skips the delete - a leak - unless
// every function wraps its work in try/catch. With RAII, stack unwinding
// cleans up automatically.
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class Buffer {
private:
    std::string label;

public:
    explicit Buffer(std::string l) : label(l) { std::cout << "    [+] " << label << std::endl; }
    ~Buffer() { std::cout << "    [-] " << label << std::endl; }
};

void riskyStep(bool fail) {
    if (fail) {
        throw std::runtime_error("sensor timeout");
    }
}

void rawVersion(bool fail) {
    Buffer* b = new Buffer("raw buffer");
    riskyStep(fail);  // if this throws...
    delete b;         // ...this never runs: LEAK
}

void rawVersionPatched(bool fail) {
    Buffer* b = new Buffer("raw buffer (patched)");
    try {
        riskyStep(fail);
    } catch (...) {
        delete b; // clean-up duplicated on the error path
        throw;    // rethrow the same exception
    }
    delete b;
}

void raiiVersion(bool fail) {
    auto b = std::make_unique<Buffer>("unique_ptr buffer");
    Buffer local("local buffer");
    riskyStep(fail);  // if this throws, BOTH are destroyed during unwinding
}

int main() {
    std::cout << "raw version:" << std::endl;
    try { rawVersion(true); } catch (const std::exception& e) { std::cout << "    caught: " << e.what() << std::endl; }
    std::cout << "    (no [-] line above: the raw buffer leaked)" << std::endl;

    std::cout << "raw version, patched with try/catch:" << std::endl;
    try { rawVersionPatched(true); } catch (const std::exception& e) { std::cout << "    caught: " << e.what() << std::endl; }

    std::cout << "RAII version - no try/catch needed for clean-up:" << std::endl;
    try { raiiVersion(true); } catch (const std::exception& e) { std::cout << "    caught: " << e.what() << std::endl; }
    return 0;
}
