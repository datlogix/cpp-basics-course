// & makes a parameter a reference: changes inside the function affect
// the caller's original variable.
#include <iostream>
#include <vector>

void doubleIt(int &x) {
    x = x * 2;
}

void minMax(std::vector<int> values, int &smallest, int &largest) {
    smallest = values[0];
    largest = values[0];
    for (int v : values) {
        if (v < smallest) smallest = v;
        if (v > largest) largest = v;
    }
}

int main() {
    int number = 5;
    doubleIt(number);
    std::cout << "number after doubleIt: " << number << std::endl; // 10

    std::vector<int> nums = {4, 9, 1, 7};
    int lo, hi;
    minMax(nums, lo, hi);
    std::cout << "min: " << lo << " max: " << hi << std::endl;

    return 0;
}
