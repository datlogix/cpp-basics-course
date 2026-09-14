// The single most common "gotcha" for beginners: int / int truncates.
#include <iostream>

int main() {
    int a = 7;
    int b = 2;

    std::cout << "int / int:       " << a / b << std::endl;               // 3, not 3.5

    double result = static_cast<double>(a) / b;
    std::cout << "cast to double:  " << result << std::endl;              // 3.5

    // Truncation also happens on assignment, not just division:
    int truncated = 9.8;
    std::cout << "int x = 9.8 ->   " << truncated << std::endl;           // 9, not rounded

    return 0;
}
