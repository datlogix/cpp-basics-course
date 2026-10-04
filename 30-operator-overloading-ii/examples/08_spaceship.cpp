// C++20's three-way comparison operator <=> ("spaceship").
// Compile with C++20:
//   g++ -std=c++20 -Wall -Wextra 08_spaceship.cpp -o 08_spaceship
#include <algorithm>
#include <compare>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// DEFAULTED: compares members in declaration order (major, then minor, then patch).
class Version {
private:
    int major, minor, patch;

public:
    Version(int ma, int mi, int pa) : major(ma), minor(mi), patch(pa) {}
    auto operator<=>(const Version&) const = default;
    bool operator==(const Version&) const = default;

    friend std::ostream& operator<<(std::ostream& os, const Version& v) {
        os << v.major << "." << v.minor << "." << v.patch;
        return os;
    }
};

// HAND-WRITTEN: students compare by average only (highest first is done in sort).
class Student {
private:
    std::string name;
    double average;

public:
    Student(std::string n, double avg) : name(n), average(avg) {}

    std::partial_ordering operator<=>(const Student& other) const {
        return average <=> other.average; // doubles give a partial_ordering
    }
    bool operator==(const Student& other) const { return average == other.average; }

    std::string getName() const { return name; }
    double getAverage() const { return average; }
};

int main() {
    Version installed(1, 4, 2);
    Version latest(1, 10, 0);

    // All six comparisons work from the two defaulted lines:
    std::cout << installed << " <  " << latest << " ? " << (installed < latest) << std::endl;
    std::cout << installed << " >= " << latest << " ? " << (installed >= latest) << std::endl;
    std::cout << installed << " != " << latest << " ? " << (installed != latest) << std::endl;

    std::set<Version> releases = {Version(2, 0, 0), Version(1, 4, 2), Version(1, 10, 0)};
    std::cout << "releases in order:";
    for (const Version& v : releases) {
        std::cout << " " << v;
    }
    std::cout << std::endl;

    std::vector<Student> cls = {{"Ama", 81.5}, {"Kojo", 74.0}, {"Esi", 92.25}};
    std::sort(cls.begin(), cls.end(), [](const Student& a, const Student& b) { return a > b; });
    std::cout << "ranked:";
    for (const Student& s : cls) {
        std::cout << " " << s.getName() << "(" << s.getAverage() << ")";
    }
    std::cout << std::endl;
    return 0;
}
