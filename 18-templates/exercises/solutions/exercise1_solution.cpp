#include <iostream>
#include <string>

template <typename T>
T minOf(T a, T b) {
    return (a < b) ? a : b;
}

template <typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
class Box {
private:
    T contents;

public:
    Box(T initial) : contents(initial) {}

    T getContents() const { return contents; }
    void setContents(T newContents) { contents = newContents; }
};

int main() {
    std::cout << minOf(3, 7) << std::endl;      // 3
    std::cout << minOf(3.5, 2.1) << std::endl;  // 2.1

    int x = 1, y = 2;
    swapValues(x, y);
    std::cout << "x=" << x << " y=" << y << std::endl;

    double d1 = 1.1, d2 = 2.2;
    swapValues(d1, d2);
    std::cout << "d1=" << d1 << " d2=" << d2 << std::endl;

    Box<std::string> nameBox("Ama");
    std::cout << nameBox.getContents() << std::endl;
    nameBox.setContents("Kofi");
    std::cout << nameBox.getContents() << std::endl;

    Box<int> countBox(42);
    std::cout << countBox.getContents() << std::endl;

    return 0;
}
