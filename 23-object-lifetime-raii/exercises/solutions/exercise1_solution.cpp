#include <iostream>
#include <string>
#include <vector>

class Tracer {
private:
    std::string name;

public:
    explicit Tracer(std::string n) : name(n) {
        std::cout << "enter " << name << std::endl;
    }
    ~Tracer() {
        std::cout << "leave " << name << std::endl;
    }
};

void partA() {
    Tracer a("a");
    for (int i = 0; i < 2; i++) {
        Tracer loop("loop" + std::to_string(i));
    }
    Tracer b("b");
}

/*
  PREDICTION for partA():
    enter a
    enter loop0
    leave loop0     <- loop dies at the end of EACH iteration's block
    enter loop1
    leave loop1
    enter b
    leave b         <- reverse order: b was constructed last, so dies first
    leave a
*/

class ReadingBuffer {
private:
    double* data;
    int capacity;
    int count = 0;

public:
    explicit ReadingBuffer(int cap) : data(new double[cap]), capacity(cap) {
        std::cout << "allocated " << capacity << std::endl;
    }

    bool add(double value) {
        if (count >= capacity) {
            return false;
        }
        data[count] = value;
        count++;
        return true;
    }

    double average() const {
        if (count == 0) {
            return 0;
        }
        double total = 0;
        for (int i = 0; i < count; i++) {
            total += data[i];
        }
        return total / count;
    }

    ~ReadingBuffer() {
        delete[] data;
        std::cout << "freed " << capacity << std::endl;
    }
};

void processReadings(const std::vector<double>& readings) {
    ReadingBuffer buffer(static_cast<int>(readings.size()));
    for (double r : readings) {
        if (r < 0) {
            std::cout << "invalid reading " << r << " - stopping early" << std::endl;
            return; // buffer's destructor still runs
        }
        buffer.add(r);
    }
    std::cout << "average = " << buffer.average() << std::endl;
}

int main() {
    std::cout << "--- Part A ---" << std::endl;
    partA();

    std::cout << "--- Part B: good data ---" << std::endl;
    processReadings({36.6, 36.9, 37.2});

    std::cout << "--- Part B: bad data ---" << std::endl;
    processReadings({36.6, -1.0, 37.2});

    return 0;
}
