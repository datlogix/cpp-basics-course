// RESULTS (Part 1, step 2)
//                 copies   moves
//   before:
//   after:
//
// REFLECTION (Part 3):
//
#include "ecg_trace.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using makersplace::clinic::EcgTrace;

const int BEATS = 50;
const int SAMPLES_PER_BEAT = 16;

EcgTrace recordBeat(int monitor) {
    const int beat[SAMPLES_PER_BEAT] = {0, 20, 60, 20, 0, -80, 1100, -250, 0, 40, 180, 220, 160, 40, 0, 0};
    std::vector<int> recording;
    for (int b = 0; b < BEATS; b++) {
        for (int s = 0; s < SAMPLES_PER_BEAT; s++) {
            recording.push_back(beat[s] + (monitor * 13 + b * 7) % 40); // a little variation
        }
    }
    std::ostringstream label;
    label << "Bed " << std::setw(2) << std::setfill('0') << monitor << " lead II";
    return EcgTrace(label.str(), recording.data(), static_cast<int>(recording.size()));
}

int main() {
    std::vector<EcgTrace> centralArchive;
    for (int monitor = 1; monitor <= 40; monitor++) {
        EcgTrace trace = recordBeat(monitor);
        centralArchive.push_back(std::move(trace)); // hand-over to the archive
    }
    std::cout << "Central archive holds " << centralArchive.size() << " recordings" << std::endl;

    // Refer bed 07's recording to a cardiologist.
    EcgTrace referral = std::move(centralArchive[6]);
    referral.print();
    centralArchive[6].print(); // Part 1 step 3: the slot it came from

    std::cout << "copies = " << EcgTrace::copies << ", moves = " << EcgTrace::moves << std::endl;
    return 0;
}
