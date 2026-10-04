// std::vector only MOVES its elements when it grows if their move
// constructor is noexcept. Otherwise it COPIES them, to stay safe if a
// move were to throw half-way through.
#include <iostream>
#include <vector>

int copies = 0;
int moves = 0;

class SafeMove { // move constructor marked noexcept
public:
    SafeMove() {}
    SafeMove(const SafeMove&) { copies++; }
    SafeMove(SafeMove&&) noexcept { moves++; }
};

class RiskyMove { // move constructor NOT marked noexcept
public:
    RiskyMove() {}
    RiskyMove(const RiskyMove&) { copies++; }
    RiskyMove(RiskyMove&&) { moves++; }
};

int main() {
    std::vector<SafeMove> safe;
    for (int i = 0; i < 1000; i++) {
        safe.push_back(SafeMove()); // each push moves the temporary in, and growth moves too
    }
    std::cout << "SafeMove (noexcept):    copies = " << copies << ", moves = " << moves << std::endl;

    copies = 0;
    moves = 0;
    std::vector<RiskyMove> risky;
    for (int i = 0; i < 1000; i++) {
        risky.push_back(RiskyMove());
    }
    std::cout << "RiskyMove (no noexcept): copies = " << copies << ", moves = " << moves << std::endl;
    std::cout << "(every copy above happened while the vector was growing)" << std::endl;
    return 0;
}
