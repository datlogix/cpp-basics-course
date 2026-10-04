// RESULTS (Part 1, step 2)
//                 copies   moves
//   before:
//   after:
//
// REFLECTION (Part 3):
//
#include "waveform.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using makersplace::energy::Waveform;

const int SAMPLES = 1000;

Waveform capture(int n) {
    // A sensor signal with an unwanted 2.5 V DC offset.
    return Waveform("capture " + std::to_string(n), 5.0, 2.5, SAMPLES);
}

Waveform removeDcOffset(Waveform w) { // takes BY VALUE, modifies, returns
    w.addOffset(-w.mean());
    return w;
}

Waveform clip(Waveform w, double maxVolts) {
    w.clipTo(maxVolts);
    return w;
}

Waveform scale(Waveform w, double gain) {
    w.multiply(gain);
    return w;
}

int main() {
    std::vector<Waveform> processed;
    for (int n = 1; n <= 50; n++) {
        Waveform raw = capture(n);
        Waveform centred = removeDcOffset(std::move(raw));
        Waveform limited = clip(std::move(centred), 4.0);
        processed.push_back(scale(std::move(limited), 0.5));
    }
    std::cout << "Processed " << processed.size() << " captures" << std::endl;
    processed[0].print();

    // Part 1 step 3: what does a moved-from Waveform hold?
    Waveform spare = capture(99);
    Waveform taken = std::move(spare);
    spare.print();

    std::cout << "copies = " << Waveform::copies << ", moves = " << Waveform::moves << std::endl;
    return 0;
}
