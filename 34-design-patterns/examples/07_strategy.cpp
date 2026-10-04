// STRATEGY: interchangeable algorithms behind one interface, swappable
// at runtime. Here: two grading schemes for the same report card.
#include <iostream>
#include <string>
#include <utility> // std::pair
#include <vector>

class GradingScheme {
public:
    virtual ~GradingScheme() = default;
    virtual std::string name() const = 0;
    virtual std::string grade(double percentage) const = 0;
};

class LetterGrades : public GradingScheme {
public:
    std::string name() const override { return "letter grades"; }
    std::string grade(double p) const override {
        if (p >= 80) return "A";
        if (p >= 70) return "B";
        if (p >= 60) return "C";
        if (p >= 50) return "D";
        return "F";
    }
};

class WassceGrades : public GradingScheme { // the West African Senior School Certificate scale
public:
    std::string name() const override { return "WASSCE grades"; }
    std::string grade(double p) const override {
        if (p >= 75) return "A1";
        if (p >= 70) return "B2";
        if (p >= 65) return "B3";
        if (p >= 60) return "C4";
        if (p >= 55) return "C5";
        if (p >= 50) return "C6";
        if (p >= 45) return "D7";
        if (p >= 40) return "E8";
        return "F9";
    }
};

class ReportCard {
private:
    std::vector<std::pair<std::string, double>> subjects;
    const GradingScheme* scheme; // the current strategy (non-owning)

public:
    explicit ReportCard(const GradingScheme& s) : scheme(&s) {}
    void setScheme(const GradingScheme& s) { scheme = &s; }
    void add(std::string subject, double pct) { subjects.push_back({subject, pct}); }

    void print() const {
        std::cout << "  Report using " << scheme->name() << ":" << std::endl;
        for (const auto& s : subjects) {
            std::cout << "    " << s.first << ": " << s.second << "% -> " << scheme->grade(s.second) << std::endl;
        }
    }
};

int main() {
    LetterGrades letters;
    WassceGrades wassce;

    ReportCard card(letters);
    card.add("Mathematics", 78);
    card.add("Integrated Science", 66);
    card.add("English", 52);
    card.print();

    card.setScheme(wassce); // swap the algorithm at runtime - ReportCard is unchanged
    card.print();
    return 0;
}
