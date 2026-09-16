// protected is accessible inside the class AND its derived classes,
// but still not from outside code.
#include <iostream>

class Base {
protected:
    int protectedValue = 10;
private:
    int privateValue = 20;
public:
    void printPrivate() {
        std::cout << "privateValue (from Base's own method): " << privateValue << std::endl;
    }
};

class Derived : public Base {
public:
    void printProtected() {
        std::cout << "protectedValue (from Derived): " << protectedValue << std::endl; // OK
        // std::cout << privateValue << std::endl; // <- uncomment: compiler error, private to Base only
    }
};

int main() {
    Derived d;
    d.printProtected();
    d.printPrivate();

    // std::cout << d.protectedValue << std::endl; // <- uncomment: compiler error, not accessible from main

    return 0;
}
