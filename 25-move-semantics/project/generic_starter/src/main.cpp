// RESULTS (Part 1, step 2)
//                 copies   moves
//   before:
//   after:
//
// REFLECTION (Part 3):
//
#include "score_sheet.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using makersplace::school::ScoreSheet;

const int STUDENTS_PER_FORM = 30;

ScoreSheet loadSheet(std::string form, std::string subject) {
    ScoreSheet sheet(form + " " + subject, STUDENTS_PER_FORM);
    for (int i = 0; i < STUDENTS_PER_FORM; i++) {
        sheet.add(40 + (i * 7 + static_cast<int>(subject.size()) * 3) % 60); // made-up scores
    }
    return sheet;
}

int main() {
    std::vector<std::string> forms = {"JHS 1", "JHS 2", "JHS 3", "SHS 1", "SHS 2", "SHS 3"};
    std::vector<std::string> subjects = {"Maths", "Science", "English", "Social", "ICT",
                                         "French", "Twi", "RME", "Creative Arts", "Career Tech"};

    std::vector<ScoreSheet> archive;
    for (const std::string& form : forms) {
        for (const std::string& subject : subjects) {
            ScoreSheet sheet = loadSheet(form, subject);
            archive.push_back(std::move(sheet)); // copies until you add move operations
        }
    }
    std::cout << "Archived " << archive.size() << " sheets" << std::endl;

    // Move JHS 3 Science out of the archive for moderation.
    ScoreSheet moderation = std::move(archive[21]);
    moderation.print();
    archive[21].print(); // Part 1 step 3: what does the moved-from slot hold?

    std::cout << "copies = " << ScoreSheet::copies << ", moves = " << ScoreSheet::moves << std::endl;
    return 0;
}
