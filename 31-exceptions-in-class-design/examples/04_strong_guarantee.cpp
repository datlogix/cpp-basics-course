// The same operation written three ways, each hit by the same failure
// part-way through:
//   NO guarantee  - the timetable is left half-updated AND inconsistent
//   BASIC         - still valid, but partly changed
//   STRONG        - either everything changes, or nothing does
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string parseLesson(const std::string& text) {
    if (text.empty()) {
        throw std::invalid_argument("empty lesson slot");
    }
    return text;
}

class Timetable {
private:
    std::vector<std::string> lessons;
    int lessonCount = 0; // INVARIANT: lessonCount == lessons.size()

public:
    Timetable() : lessons({"Maths", "English", "Science"}), lessonCount(3) {}

    // NO GUARANTEE: changes state, then fails - and breaks the invariant.
    void replaceNoGuarantee(const std::vector<std::string>& slots) {
        lessons.clear();
        lessonCount = static_cast<int>(slots.size()); // updated too early!
        for (const std::string& s : slots) {
            lessons.push_back(parseLesson(s));
        }
    }

    // BASIC: the invariant always holds, but a failure leaves a partial update.
    void replaceBasic(const std::vector<std::string>& slots) {
        lessons.clear();
        lessonCount = 0;
        for (const std::string& s : slots) {
            lessons.push_back(parseLesson(s));
            lessonCount++;
        }
    }

    // STRONG: build on the side, then commit with operations that can't throw.
    void replaceStrong(const std::vector<std::string>& slots) {
        std::vector<std::string> updated;
        for (const std::string& s : slots) {
            updated.push_back(parseLesson(s)); // may throw - *this untouched
        }
        lessons.swap(updated); // commit: swap never throws
        lessonCount = static_cast<int>(lessons.size());
    }

    void print(const std::string& label) const {
        std::cout << "  " << label << ": " << lessons.size() << " lessons stored, lessonCount says "
                  << lessonCount << (lessonCount == static_cast<int>(lessons.size()) ? "" : "  <- BROKEN")
                  << std::endl;
    }
};

int main() {
    std::vector<std::string> badUpdate = {"Robotics", "Coding", "", "French"}; // 3rd slot is invalid

    Timetable a, b, c;

    try { a.replaceNoGuarantee(badUpdate); } catch (const std::exception&) {}
    a.print("no guarantee");

    try { b.replaceBasic(badUpdate); } catch (const std::exception&) {}
    b.print("basic       ");

    try { c.replaceStrong(badUpdate); } catch (const std::exception&) {}
    c.print("strong      ");
    std::cout << "  (strong: the original 3 lessons are still there, untouched)" << std::endl;
    return 0;
}
