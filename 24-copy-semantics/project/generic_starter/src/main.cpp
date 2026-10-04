// TODO (Part 3): How many lines of code did the Rule of Zero version
// save, and which bugs is it immune to?
//
#include "score_sheet.h"

#include <iostream>

using makersplace::school::ScoreSheet;

int main() {
    ScoreSheet official("JHS 3 Science (official)", 8);
    double results[] = {47, 52, 68, 45, 90, 38, 49, 71};
    for (double r : results) {
        official.add(r);
    }
    official.print();

    // TODO (Part 1): uncomment once the copy constructor and copy
    // assignment operator exist. Running this WITHOUT them would delete
    // the same array twice.
    //
    // ScoreSheet whatIf = official;   // copy constructor
    // whatIf.addBonus(5);
    // official.print();               // must be unchanged
    // whatIf.print();
    //
    // whatIf = official;              // copy assignment: reset the experiment
    // whatIf.print();

    return 0;
}
