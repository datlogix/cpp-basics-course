#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<double> temperatures = {28.5, 31.2, 25.0, 33.8, 29.1};

    std::sort(temperatures.begin(), temperatures.end());
    std::cout << "-- sorted --" << std::endl;
    for (double t : temperatures) {
        std::cout << t << std::endl;
    }

    auto highIt = std::max_element(temperatures.begin(), temperatures.end());
    auto lowIt = std::min_element(temperatures.begin(), temperatures.end());
    std::cout << "Highest: " << *highIt << std::endl;
    std::cout << "Lowest: " << *lowIt << std::endl;

    int hotDays = std::count_if(temperatures.begin(), temperatures.end(),
        [](double t) { return t > 30.0; });
    std::cout << "Hot days: " << hotDays << std::endl;

    std::vector<double> fahrenheit(temperatures.size());
    std::transform(temperatures.begin(), temperatures.end(), fahrenheit.begin(),
        [](double c) { return c * 9.0 / 5.0 + 32.0; });

    std::cout << "-- Fahrenheit --" << std::endl;
    for (double f : fahrenheit) {
        std::cout << f << std::endl;
    }

    return 0;
}
