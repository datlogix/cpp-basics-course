// public, protected and private inheritance side by side.
// Lines that would NOT compile are commented out with the reason.
#include <iostream>

class Timer {
private:
    int ticks = 0;

public:
    void start() { ticks = 0; }
    void tick() { ticks++; }
    int elapsed() const { return ticks; }

protected:
    void reset() { ticks = 0; }
};

// PUBLIC inheritance: "is-a". Timer's public members stay public.
class Stopwatch : public Timer {
public:
    void lap() { std::cout << "  lap at " << elapsed() << std::endl; }
};

// PRIVATE inheritance: "is implemented in terms of". Timer's public
// members become PRIVATE in LessonClock - usable inside, hidden outside.
class LessonClock : private Timer {
public:
    void beginLesson() { start(); }
    void minutePasses() { tick(); }
    bool overrun() const { return elapsed() > 45; }
};

// The same idea with COMPOSITION - usually the clearer choice.
class LessonClockComposed {
private:
    Timer timer; // has-a
public:
    void beginLesson() { timer.start(); }
    void minutePasses() { timer.tick(); }
    bool overrun() const { return timer.elapsed() > 45; }
};

// PROTECTED inheritance: public base members become protected. Rare.
class TestTimer : protected Timer {
public:
    void run() {
        start();
        tick();
        reset(); // protected members are usable inside, as always
    }
};

void printElapsed(const Timer& t) {
    std::cout << "  elapsed: " << t.elapsed() << std::endl;
}

int main() {
    Stopwatch sw;
    sw.start();     // OK: public inheritance keeps start() public
    sw.tick();
    sw.lap();
    printElapsed(sw); // OK: a Stopwatch IS-A Timer

    LessonClock lc;
    lc.beginLesson();
    for (int i = 0; i < 50; i++) {
        lc.minutePasses();
    }
    std::cout << "  lesson overrun? " << (lc.overrun() ? "yes" : "no") << std::endl;
    // lc.start();       // ERROR: start() is private in LessonClock
    // printElapsed(lc); // ERROR: a LessonClock is NOT usable as a Timer from outside

    LessonClockComposed lc2;
    lc2.beginLesson();
    std::cout << "  composed version overrun? " << (lc2.overrun() ? "yes" : "no") << std::endl;

    TestTimer tt;
    tt.run();
    // tt.elapsed();     // ERROR: elapsed() is protected in TestTimer
    return 0;
}
