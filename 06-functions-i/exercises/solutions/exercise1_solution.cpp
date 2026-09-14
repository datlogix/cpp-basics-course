#include <iostream>
#include <vector>

bool isEven(int n) {
    return n % 2 == 0;
}

double average(std::vector<double> values) {
    double sum = 0;
    for (double v : values) {
        sum += v;
    }
    return sum / values.size();
}

void printLine(int length) {
    for (int i = 0; i < length; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << isEven(4) << std::endl; // 1 (true)
    std::cout << isEven(7) << std::endl; // 0 (false)

    std::vector<double> nums = {10.0, 20.0, 30.0};
    std::cout << average(nums) << std::endl; // 20

    printLine(5);
    printLine(10);

    return 0;
}
