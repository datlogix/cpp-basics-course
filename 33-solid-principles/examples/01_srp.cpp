// Single Responsibility Principle: one reason to change per class.
// BEFORE: ReportCard does grading, formatting AND saving.
// AFTER:  three small classes, each with one job.
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace before {

class ReportCard {
private:
    std::string student;
    std::vector<double> scores;

public:
    ReportCard(std::string s, std::vector<double> sc) : student(s), scores(sc) {}

    double average() const { // reason to change #1: grading policy
        double total = 0;
        for (double s : scores) total += s;
        return scores.empty() ? 0 : total / scores.size();
    }

    std::string toText() const { // reason to change #2: presentation
        std::ostringstream out;
        out << "REPORT CARD: " << student << " - average " << average();
        return out.str();
    }

    void saveToFile(const std::string& filename) const { // reason to change #3: storage
        std::ofstream file(filename, std::ios::app);
        file << student << "," << average() << "\n";
    }
};

} // namespace before

namespace after {

class ReportCard { // grading ONLY
private:
    std::string student;
    std::vector<double> scores;

public:
    ReportCard(std::string s, std::vector<double> sc) : student(s), scores(sc) {}
    std::string getStudent() const { return student; }
    double average() const {
        double total = 0;
        for (double s : scores) total += s;
        return scores.empty() ? 0 : total / scores.size();
    }
};

class ReportCardFormatter { // presentation ONLY
public:
    std::string toText(const ReportCard& card) const {
        std::ostringstream out;
        out << "REPORT CARD: " << card.getStudent() << " - average " << card.average();
        return out.str();
    }
};

class ReportCardRepository { // storage ONLY
private:
    std::string filename;

public:
    explicit ReportCardRepository(std::string f) : filename(f) {}
    void save(const ReportCard& card) const {
        std::ofstream file(filename, std::ios::app);
        file << card.getStudent() << "," << card.average() << "\n";
    }
};

} // namespace after

int main() {
    before::ReportCard old("Ama", {78, 85, 91});
    std::cout << old.toText() << std::endl;
    old.saveToFile("report_cards.csv");

    after::ReportCard card("Ama", {78, 85, 91});
    after::ReportCardFormatter formatter;
    after::ReportCardRepository repository("report_cards.csv");
    std::cout << formatter.toText(card) << std::endl;
    repository.save(card);

    // A design change now touches ONLY the formatter; a move to a database
    // touches ONLY the repository; a new grading rule touches ONLY ReportCard.
    return 0;
}
