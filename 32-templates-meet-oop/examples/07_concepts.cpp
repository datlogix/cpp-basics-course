// C++20 concepts: name what a template needs from its type parameter.
// Compile with C++20:
//   g++ -std=c++20 -Wall -Wextra 07_concepts.cpp -o 07_concepts
#include <concepts>
#include <iostream>
#include <string>
#include <vector>

// A concept built from standard-library concepts:
template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// A concept with a requires-expression: "these operations must compile".
template <typename T>
concept HasArea = requires(const T& shape) {
    { shape.area() } -> std::convertible_to<double>;
    { shape.name() } -> std::convertible_to<std::string>;
};

template <Numeric T> // only numeric types allowed
class Statistics {
private:
    std::vector<T> values;

public:
    void add(T v) { values.push_back(v); }
    double mean() const {
        double total = 0;
        for (T v : values) total += v;
        return values.empty() ? 0 : total / values.size();
    }
};

template <HasArea S>
double totalArea(const std::vector<S>& shapes) {
    double total = 0;
    for (const S& s : shapes) {
        std::cout << "  " << s.name() << ": " << s.area() << std::endl;
        total += s.area();
    }
    return total;
}

struct Square {
    double side;
    double area() const { return side * side; }
    std::string name() const { return "square"; }
};

struct Label { // has a name() but NO area()
    std::string text;
    std::string name() const { return text; }
};

int main() {
    Statistics<int> scores;
    scores.add(70);
    scores.add(90);
    std::cout << "mean score: " << scores.mean() << std::endl;

    // Statistics<std::string> words;
    //   ERROR (clear!): template constraint failure for ... requires Numeric<T> class Statistics
    //                   note: constraints not satisfied

    std::vector<Square> tiles = {{0.5}, {0.5}, {1.0}};
    double total = totalArea(tiles);
    std::cout << "total tile area: " << total << std::endl;

    // std::vector<Label> labels = {{"exit"}};
    // totalArea(labels);
    //   ERROR (clear!): constraints not satisfied ... the required expression 'shape.area()' is invalid

    std::cout << "int is Numeric? " << Numeric<int> << ", std::string is Numeric? "
              << Numeric<std::string> << std::endl;
    std::cout << "Square HasArea? " << HasArea<Square> << ", Label HasArea? " << HasArea<Label>
              << std::endl;
    return 0;
}
