// A program with a LOGIC bug: the class average is wrong. Find it with gdb.
//
//   g++ -std=c++17 -Wall -Wextra -g -O0 07_debugger_demo.cpp -o demo
//   gdb ./demo
//
// A walkthrough:
//   (gdb) break Gradebook::average     <- pause when average() is called
//   (gdb) run
//   (gdb) print scores                 <- the vector: {72, 85, 64, 90}
//   (gdb) next                         <- step line by line...
//   (gdb) next
//   (gdb) print i                      <- what is i on the first pass of the loop?
//   (gdb) print total
//   (gdb) next   (repeat, printing i and total each time)
//   ...you'll see the first score is never added. Why?
//   (gdb) backtrace                    <- shows main -> printReport -> average
//   (gdb) quit
//
// In VS Code: click left of a line number to set a breakpoint, press F5,
// and use the Step Over / Step Into buttons and the Variables panel.
#include <iostream>
#include <string>
#include <vector>

class Gradebook {
private:
    std::string subject;
    std::vector<double> scores;

public:
    explicit Gradebook(std::string s) : subject(s) {}
    void add(double score) { scores.push_back(score); }

    double average() const {
        double total = 0;
        for (size_t i = 1; i < scores.size(); i++) { // the bug is on this line
            total += scores[i];
        }
        return scores.empty() ? 0 : total / scores.size();
    }

    std::string getSubject() const { return subject; }
};

void printReport(const Gradebook& g) {
    std::cout << g.getSubject() << " average: " << g.average() << " (expected 77.75)" << std::endl;
}

int main() {
    Gradebook maths("Mathematics");
    maths.add(72);
    maths.add(85);
    maths.add(64);
    maths.add(90);
    printReport(maths);
    return 0;
}
