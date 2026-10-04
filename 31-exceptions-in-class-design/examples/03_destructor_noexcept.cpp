// Destructors must never let an exception escape. If clean-up can fail,
// offer a close() that CAN throw, and have the destructor call it inside
// try/catch(...) so nothing escapes.
#include <iostream>
#include <stdexcept>
#include <string>

class NetworkLink {
private:
    std::string server;
    bool open = true;
    bool failOnClose;

public:
    NetworkLink(std::string s, bool fail) : server(s), failOnClose(fail) {
        std::cout << "  connected to " << server << std::endl;
    }

    // Callers who care about clean-up errors call this themselves.
    void close() {
        if (!open) {
            return;
        }
        open = false;
        if (failOnClose) {
            throw std::runtime_error("could not close link to " + server + " cleanly");
        }
        std::cout << "  link to " << server << " closed" << std::endl;
    }

    ~NetworkLink() { // implicitly noexcept
        try {
            close();
        } catch (const std::exception& e) {
            // Log and swallow: letting this escape would call std::terminate().
            std::cout << "  (destructor) ignored: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "  (destructor) ignored an unknown error" << std::endl;
        }
    }
};

int main() {
    std::cout << "1. Caller closes explicitly and handles the error:" << std::endl;
    try {
        NetworkLink link("results.makersplace.local", true);
        link.close();
    } catch (const std::exception& e) {
        std::cout << "  caller handled: " << e.what() << std::endl;
    }

    std::cout << "2. Caller relies on the destructor:" << std::endl;
    {
        NetworkLink link("backup.makersplace.local", true);
    } // destructor swallows the error - the program keeps running

    std::cout << "3. An exception is already in flight when the destructor runs:" << std::endl;
    try {
        NetworkLink link("sync.makersplace.local", true);
        throw std::runtime_error("upload failed");
    } catch (const std::exception& e) {
        std::cout << "  caught: " << e.what() << std::endl;
    }
    std::cout << "Program still running - no std::terminate." << std::endl;
    return 0;
}
