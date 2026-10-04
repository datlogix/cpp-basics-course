// Module 21 Project - Track A: School Club Registry, redesigned
// See project/README.md for requirements.
#include <iostream>
#include <string>
#include <vector>

class Student {
private:
    static int nextId;

    const int id;
    std::string name;
    std::string form = "Unassigned";

public:
    Student(std::string n, std::string f);
    // TODO: make this delegate to the two-argument constructor with form "Unassigned"
    //       (replace the body-less stub below with  : Student(n, "Unassigned") {} )
    explicit Student(std::string n) : id(nextId++), name(n) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getForm() const { return form; }
};

int Student::nextId = 1;

Student::Student(std::string n, std::string f) : id(nextId), name(n), form(f) {
    nextId++;
}

class Club {
private:
    // INVARIANT: members.size() <= capacity, and no student ID appears twice.
    static int membershipCount;

    std::string name;
    const int capacity;
    std::vector<Student> members;

public:
    Club(std::string n, int cap);

    bool join(const Student& s);   // TODO
    bool leave(int studentId);     // TODO
    bool isMember(int studentId) const; // TODO
    void printRegister() const;    // TODO

    static int totalMemberships() { return membershipCount; }
};

int Club::membershipCount = 0;

Club::Club(std::string n, int cap) : name(n), capacity(cap >= 1 ? cap : 10) {}

bool Club::join(const Student& s) {
    // TODO: refuse if full or already a member; otherwise add and count it
    (void)s;
    return false;
}

bool Club::leave(int studentId) {
    // TODO: remove the student if present
    (void)studentId;
    return false;
}

bool Club::isMember(int studentId) const {
    // TODO
    (void)studentId;
    return false;
}

void Club::printRegister() const {
    // TODO: print the club name, capacity, and every member
}

int main() {
    Student ama("Ama", "JHS 2");
    Student kojo("Kojo");

    Club robotics("Robotics Club", 2);
    // TODO: exercise every method, including a refused join for a full club
    // and a refused duplicate join, then print the register and
    // Club::totalMemberships().

    (void)ama;  // remove these two lines once you use ama and kojo
    (void)kojo;
    return 0;
}
