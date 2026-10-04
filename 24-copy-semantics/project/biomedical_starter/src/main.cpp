// TODO (Part 3): How many lines of code did the Rule of Zero version
// save, and which bugs is it immune to?
//
#include "ecg_trace.h"

using makersplace::clinic::EcgTrace;

int main() {
    // One simplified heartbeat: baseline, P wave, QRS complex, T wave.
    const int beat[] = {0, 20, 60, 20, 0, -80, 1100, -250, 0, 40, 180, 220, 160, 40, 0, 0};
    EcgTrace original("Patient CL-0001 lead II (ORIGINAL)", beat, 16);
    original.print();

    // TODO (Part 1): uncomment once the copy constructor and copy
    // assignment operator exist. Running this WITHOUT them would delete
    // the same array twice.
    //
    // EcgTrace working = original;    // copy constructor
    // working.smooth();
    // original.print();               // must be unchanged - it's a medical record
    // working.print();
    //
    // working = original;             // copy assignment: restore the working copy
    // working.print();

    return 0;
}
