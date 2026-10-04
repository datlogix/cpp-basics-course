// Member initializer lists and default member initializers.
// A const member and a reference member can ONLY be set in the
// initializer list - assignment in the body would not compile.
#include <iostream>
#include <string>

class Ward {
private:
    std::string name;
public:
    explicit Ward(std::string n) : name(n) {}
    std::string getName() const { return name; }
};

class Patient {
private:
    const std::string folderNumber; // const: fixed for the patient's lifetime
    Ward& ward;                     // reference: must refer to a ward from birth
    double temperatureC = 37.0;     // default member initializer
    bool admitted = true;           // default member initializer

public:
    Patient(std::string folder, Ward& w)
        : folderNumber(folder), ward(w) {} // temperatureC and admitted use defaults

    Patient(std::string folder, Ward& w, double temp)
        : folderNumber(folder), ward(w), temperatureC(temp) {} // overrides one default

    void print() const {
        std::cout << folderNumber << " in " << ward.getName()
                  << ", temp " << temperatureC << " C"
                  << (admitted ? ", admitted" : "") << std::endl;
    }
};

int main() {
    Ward maternity("Maternity");
    Ward childrens("Children's Ward");

    Patient p1("KBTH-0001", maternity);
    Patient p2("KBTH-0002", childrens, 38.4);

    p1.print();
    p2.print();
    return 0;
}
