// TODO (Part 3): How many lines of code did the Rule of Zero version
// save, and which bugs is it immune to?
//
#include "waveform.h"

using makersplace::energy::Waveform;

int main() {
    Waveform mains("Mains 230 V RMS", 325.0, 200);
    mains.print();

    // TODO (Part 1): uncomment once the copy constructor and copy
    // assignment operator exist. Running this WITHOUT them would delete
    // the same array twice.
    //
    // Waveform processed = mains;     // copy constructor
    // processed.clip(250.0);
    // mains.print();                  // must be unchanged
    // processed.print();
    //
    // processed = mains;              // copy assignment: restore
    // processed.print();

    return 0;
}
