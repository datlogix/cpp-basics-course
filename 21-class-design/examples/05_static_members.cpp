// static members belong to the CLASS, not to any one object.
// Here a static counter hands out unique student IDs.
#include <iostream>
#include <string>

class Student {
private:
    static int nextId;             // ONE shared counter (declared here)
    static const int MAX_SCORE = 100; // a shared constant

    int id;
    std::string name;

public:
    explicit Student(std::string n) : id(nextId), name(n) {
        nextId++;
    }

    int getId() const { return id; }
    std::string getName() const { return name; }

    // A static method: no object, no 'this' - only static members.
    static int studentsCreated() { return nextId - 1; }
    static int maxScore() { return MAX_SCORE; }
};

int Student::nextId = 1; // ...and DEFINED once, outside the class

int main() {
    std::cout << "Students so far: " << Student::studentsCreated() << std::endl;

    Student a("Abena");
    Student b("Kofi");
    Student c("Nana");

    std::cout << a.getName() << " has ID " << a.getId() << std::endl;
    std::cout << b.getName() << " has ID " << b.getId() << std::endl;
    std::cout << c.getName() << " has ID " << c.getId() << std::endl;

    std::cout << "Students so far: " << Student::studentsCreated() << std::endl;
    std::cout << "Highest possible score: " << Student::maxScore() << std::endl;
    return 0;
}
