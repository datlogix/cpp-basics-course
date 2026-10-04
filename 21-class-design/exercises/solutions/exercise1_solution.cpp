#include <iomanip>
#include <iostream>

class ClockTime {
private:
    static int count;

    int hours = 0;
    int minutes = 0;

public:
    ClockTime(int h, int m) : hours(h), minutes(m) {
        if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
            hours = 0;
            minutes = 0;
        }
        count++;
    }

    explicit ClockTime(int h) : ClockTime(h, 0) {}

    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }

    void print() const;
    void addMinutes(int m);

    static int created() { return count; }
};

int ClockTime::count = 0;

void ClockTime::print() const {
    std::cout << std::setfill('0') << std::setw(2) << hours << ":"
              << std::setw(2) << minutes << std::setfill(' ') << std::endl;
}

void ClockTime::addMinutes(int m) {
    int total = hours * 60 + minutes + m;
    total = total % (24 * 60); // wrap past midnight
    hours = total / 60;
    minutes = total % 60;
}

int main() {
    ClockTime lesson(9, 5);
    ClockTime lunch(12);
    ClockTime late(23, 50);
    ClockTime invalid(25, 70);

    lesson.print();   // 09:05
    lunch.print();    // 12:00
    invalid.print();  // 00:00

    late.addMinutes(20);
    late.print();     // 00:10

    lesson.addMinutes(135);
    lesson.print();   // 11:20

    std::cout << "ClockTime objects created: " << ClockTime::created() << std::endl;
    return 0;
}
