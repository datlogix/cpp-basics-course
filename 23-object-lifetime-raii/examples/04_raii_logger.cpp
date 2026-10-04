// An RAII class: the constructor ACQUIRES a resource (opens a log file
// and writes a header), and the destructor RELEASES it (writes a footer
// and closes the file). The user of the class can't forget either step.
#include <fstream>
#include <iostream>
#include <string>

class SessionLog {
private:
    std::ofstream file;
    std::string sessionName;
    int entries = 0;

public:
    SessionLog(std::string filename, std::string session)
        : file(filename), sessionName(session) {
        file << "=== START " << sessionName << " ===" << std::endl;
        std::cout << "(log opened)" << std::endl;
    }

    void record(std::string message) {
        entries++;
        file << entries << ": " << message << std::endl;
    }

    ~SessionLog() {
        file << "=== END " << sessionName << " (" << entries << " entries) ===" << std::endl;
        std::cout << "(log closed)" << std::endl;
        // file's own destructor runs after this body and closes the file -
        // std::ofstream is itself an RAII class.
    }
};

void runLabSession() {
    SessionLog log("session_log.txt", "Robotics lab, Saturday");
    log.record("Line-following robot calibrated");
    log.record("Ultrasonic sensor tested: 32 cm");
    log.record("Session complete");
} // log's destructor runs here - footer written, file closed

int main() {
    runLabSession();

    std::ifstream in("session_log.txt");
    std::string line;
    std::cout << "Contents of session_log.txt:" << std::endl;
    while (std::getline(in, line)) {
        std::cout << "  " << line << std::endl;
    }
    return 0;
}
