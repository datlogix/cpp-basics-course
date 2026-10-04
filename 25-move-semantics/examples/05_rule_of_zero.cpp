// The Rule of Zero: a class made of std::string and std::vector members
// gets correct, FAST copies and moves without writing any special
// member functions. Moving it just moves each member.
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Recording {
private:
    std::string patientId;
    std::vector<double> samples;

public:
    Recording(std::string id, int n) : patientId(id), samples(n, 0.0) {}

    int size() const { return static_cast<int>(samples.size()); }
    const double* address() const { return samples.data(); } // where the vector's array lives
    std::string getId() const { return patientId; }
};

int main() {
    Recording overnight("CL-0042", 1000000);
    std::cout << "Original array at " << overnight.address() << std::endl;

    std::vector<Recording> archive;
    archive.push_back(std::move(overnight)); // compiler-generated move constructor

    std::cout << "Archived array at " << archive[0].address() << "  <- same array, no copying"
              << std::endl;
    std::cout << "Archived " << archive[0].getId() << " with " << archive[0].size() << " samples"
              << std::endl;
    std::cout << "Moved-from recording now has " << overnight.size() << " samples" << std::endl;
    return 0;
}
