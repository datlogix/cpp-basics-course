// operator[] in two versions: non-const (read AND write) and const
// (read only). This one also checks bounds, which plain arrays don't.
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Gradebook {
private:
    std::string subject;
    std::vector<double> scores;

    void checkIndex(int i) const {
        if (i < 0 || i >= static_cast<int>(scores.size())) {
            throw std::out_of_range("Gradebook index " + std::to_string(i) + " is out of range");
        }
    }

public:
    Gradebook(std::string s, int students) : subject(s), scores(students, 0.0) {}

    double& operator[](int i) { // non-const: g[2] = 75;
        checkIndex(i);
        return scores[i];
    }

    const double& operator[](int i) const { // const: reading a const Gradebook
        checkIndex(i);
        return scores[i];
    }

    int size() const { return static_cast<int>(scores.size()); }
};

double average(const Gradebook& g) { // g is const, so the const operator[] is used
    double total = 0;
    for (int i = 0; i < g.size(); i++) {
        total += g[i];
        // g[i] = 0;  // ERROR: the const version returns a const reference
    }
    return total / g.size();
}

int main() {
    Gradebook maths("Mathematics", 4);
    maths[0] = 72;
    maths[1] = 85;
    maths[2] = 64;
    maths[3] = 90;
    maths[2] += 5; // after a re-mark

    std::cout << "student 2 now has " << maths[2] << std::endl;
    std::cout << "class average: " << average(maths) << std::endl;

    try {
        maths[10] = 50;
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}
