// Tracing the copy constructor and copy assignment operator to see
// exactly WHEN copies happen.
#include <iostream>
#include <string>
#include <vector>

class Gradebook {
private:
    std::string subject;

public:
    explicit Gradebook(std::string s) : subject(s) {
        std::cout << "    constructor (" << subject << ")" << std::endl;
    }

    // Copy constructor: makes a NEW object from an existing one.
    Gradebook(const Gradebook& other) : subject(other.subject) {
        std::cout << "    COPY CONSTRUCTOR (copying " << other.subject << ")" << std::endl;
    }

    // Copy assignment: replaces the contents of an EXISTING object.
    Gradebook& operator=(const Gradebook& other) {
        std::cout << "    COPY ASSIGNMENT (" << subject << " becomes " << other.subject << ")"
                  << std::endl;
        subject = other.subject;
        return *this;
    }

    std::string getSubject() const { return subject; }

    ~Gradebook() {
        std::cout << "    destructor (" << subject << ")" << std::endl;
    }
};

void printByValue(Gradebook g) { // g is a COPY
    std::cout << "    inside printByValue: " << g.getSubject() << std::endl;
}

void printByReference(const Gradebook& g) { // no copy at all
    std::cout << "    inside printByReference: " << g.getSubject() << std::endl;
}

Gradebook makeGradebook() {
    Gradebook local("Physics");
    return local; // the compiler usually builds 'local' directly in the caller's
                  // variable, so NO copy is printed here ("copy elision", Module 25)
}

int main() {
    std::cout << "1. Create a:" << std::endl;
    Gradebook a("Maths");

    std::cout << "2. Gradebook b = a;" << std::endl;
    Gradebook b = a;

    std::cout << "3. Pass by value:" << std::endl;
    printByValue(a);

    std::cout << "4. Pass by const reference:" << std::endl;
    printByReference(a);

    std::cout << "5. push_back into a vector:" << std::endl;
    std::vector<Gradebook> shelf;
    shelf.reserve(5); // stops the vector moving elements around as it grows
    shelf.push_back(a);

    std::cout << "6. Return by value:" << std::endl;
    Gradebook p = makeGradebook();

    std::cout << "7. Assign to an EXISTING object (b = p):" << std::endl;
    b = p;

    std::cout << "8. End of main - everything is destroyed:" << std::endl;
    return 0;
}
