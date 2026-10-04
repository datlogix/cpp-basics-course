// Function objects (functors): classes with operator(). They carry data
// chosen when they're created - exactly what STL algorithms need.
// Each functor is shown next to the equivalent lambda.
#include <algorithm>
#include <iostream>
#include <vector>

class IsAbove {
private:
    double threshold;

public:
    explicit IsAbove(double t) : threshold(t) {}
    bool operator()(double value) const { return value > threshold; }
};

class CelsiusToFahrenheit {
public:
    double operator()(double c) const { return c * 9.0 / 5.0 + 32.0; }
};

// A functor with STATE that changes as it's used.
class RunningAverage {
private:
    double total = 0;
    int count = 0;

public:
    void operator()(double value) {
        total += value;
        count++;
    }
    double result() const { return count == 0 ? 0 : total / count; }
};

int main() {
    std::vector<double> temps = {36.8, 38.4, 37.1, 39.0, 36.5, 38.1};

    IsAbove fever(38.0);
    std::cout << "fever(39.2) = " << (fever(39.2) ? "true" : "false") << "  <- an object, called like a function"
              << std::endl;

    int withFunctor = std::count_if(temps.begin(), temps.end(), IsAbove(38.0));
    double limit = 38.0;
    int withLambda = std::count_if(temps.begin(), temps.end(), [limit](double t) { return t > limit; });
    std::cout << "readings above 38 C: " << withFunctor << " (functor), " << withLambda << " (lambda)"
              << std::endl;

    std::vector<double> fahrenheit(temps.size());
    std::transform(temps.begin(), temps.end(), fahrenheit.begin(), CelsiusToFahrenheit());
    std::cout << "first reading in F: " << fahrenheit[0] << std::endl;

    RunningAverage avg = std::for_each(temps.begin(), temps.end(), RunningAverage());
    std::cout << "average temperature: " << avg.result() << std::endl;
    return 0;
}
