// std::map stores key/value pairs, looked up by key instead of position.
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, double> componentValues;

    componentValues["R1"] = 220.0;
    componentValues["C1"] = 0.000001;
    componentValues["L1"] = 0.05;

    std::cout << "R1 = " << componentValues["R1"] << std::endl;

    if (componentValues.count("R2") == 0) {
        std::cout << "R2 not found." << std::endl;
    }

    std::cout << "-- all components, sorted by key --" << std::endl;
    for (const auto& pair : componentValues) {
        std::cout << pair.first << " = " << pair.second << std::endl;
    }

    return 0;
}
