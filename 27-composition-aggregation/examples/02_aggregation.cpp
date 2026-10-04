// AGGREGATION: a Department GROUPS Teachers but does not own them.
// The teachers exist before the department and survive after it.
#include <iostream>
#include <string>
#include <vector>

class Teacher {
private:
    std::string name;

public:
    explicit Teacher(std::string n) : name(n) { std::cout << "  [+] teacher " << name << std::endl; }
    ~Teacher() { std::cout << "  [-] teacher " << name << std::endl; }
    std::string getName() const { return name; }
};

class Department {
private:
    std::string name;
    std::vector<Teacher*> members; // NON-owning: aggregation

public:
    explicit Department(std::string n) : name(n) { std::cout << "  [+] department " << name << std::endl; }
    ~Department() { std::cout << "  [-] department " << name << " (teachers are NOT deleted)" << std::endl; }

    void add(Teacher& t) { members.push_back(&t); }

    void print() const {
        std::cout << "  " << name << ":";
        for (const Teacher* t : members) {
            std::cout << " " << t->getName();
        }
        std::cout << std::endl;
    }
};

int main() {
    // The owner of the teachers is main (they're local variables here).
    Teacher mensah("Mr Mensah");
    Teacher addo("Mrs Addo");
    Teacher osei("Dr Osei");

    {
        Department science("Science");
        Department stem("STEM Club staff");

        science.add(mensah);
        science.add(osei);
        stem.add(osei); // one teacher, two departments - allowed in aggregation
        stem.add(addo);

        science.print();
        stem.print();
        std::cout << "Departments are closed down:" << std::endl;
    }

    std::cout << "The teachers still exist: " << mensah.getName() << ", " << addo.getName()
              << ", " << osei.getName() << std::endl;
    std::cout << "end of main:" << std::endl;
    return 0;
}
