// A class template generates a separate real class for each type you
// use it with - exactly how std::vector<T> itself is built.
#include <iostream>

template <typename T>
class Pair {
private:
    T first;
    T second;

public:
    Pair(T a, T b) : first(a), second(b) {}

    T getFirst() const { return first; }
    T getSecond() const { return second; }
    T sum() const { return first + second; }
};

int main() {
    Pair<int> intPair(3, 4);
    std::cout << "intPair sum: " << intPair.sum() << std::endl;

    Pair<double> doublePair(1.5, 2.5);
    std::cout << "doublePair sum: " << doublePair.sum() << std::endl;

    return 0;
}
