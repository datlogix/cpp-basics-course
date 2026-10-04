// std::move is just a CAST to rvalue - it gives permission to move.
// After moving, the source is valid but its contents are unspecified:
// don't rely on them.
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    std::string report = "Term 1 report for JHS 2: Mathematics 78, Science 84, English 71";

    std::vector<std::string> archive;

    archive.push_back(report);            // COPY: report is an lvalue
    std::cout << "After copy, report still holds: \"" << report << "\"" << std::endl;

    archive.push_back(std::move(report)); // MOVE: we promise not to use report's contents again
    std::cout << "After move, report holds: \"" << report << "\" (moved-from: don't rely on this)"
              << std::endl;

    report = "Term 2 report"; // assigning a new value to a moved-from object is fine
    std::cout << "Reused: \"" << report << "\"" << std::endl;

    std::cout << "Archive has " << archive.size() << " reports" << std::endl;

    // std::move does NOTHING by itself. Here its result is only bound to a
    // reference - no move constructor or move assignment ever runs:
    std::string name = "Abena";
    std::string&& sameName = std::move(name); // just a cast to rvalue
    std::cout << "name is still \"" << name << "\" (and sameName is \"" << sameName << "\")"
              << std::endl;
    return 0;
}
