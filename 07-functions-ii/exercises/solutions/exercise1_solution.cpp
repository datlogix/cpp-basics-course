#include <iostream>

void swapValues(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int maxOf(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

double maxOf(double a, double b) {
    if (a > b) {
        return a;
    }
    return b;
}

int sumUpTo(int n) {
    if (n <= 0) {           // base case
        return 0;
    }
    return n + sumUpTo(n - 1); // recursive case
}

int main() {
    int x = 3, y = 8;
    swapValues(x, y);
    std::cout << "x=" << x << " y=" << y << std::endl; // x=8 y=3

    std::cout << maxOf(4, 9) << std::endl;      // 9
    std::cout << maxOf(3.5, 2.1) << std::endl;  // 3.5

    std::cout << sumUpTo(5) << std::endl;  // 15
    std::cout << sumUpTo(10) << std::endl; // 55

    return 0;
}
