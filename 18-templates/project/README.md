# Module 18 Project — A Generic Statistics Toolkit

Pick **one** track. All three build a `template <typename T>` class
computing descriptive statistics (mean, min, max, standard deviation)
for a series of any numeric type — the direct generalization of every
`average()`/`min`/`max` calculation you've written since Module 5.

## Common core (build this first, in every track)

```cpp
template <typename T>
class Statistics {
private:
    std::vector<T> values;

public:
    void addValue(T v) { values.push_back(v); }

    double mean() const { /* sum / count, guard divide-by-zero */ }
    T minimum() const { /* smallest value, e.g. via std::min_element */ }
    T maximum() const { /* largest value, e.g. via std::max_element */ }
    double standardDeviation() const {
        // 1. compute the mean
        // 2. sum of (value - mean)^2 for every value
        // 3. divide by count, then sqrt() the result (#include <cmath>)
    }
};
```

## Track A — Generic: Grade Statistics

1. Build `Statistics<double>` and feed it a class's exam scores.
2. Print the mean, min, max, and standard deviation.
3. Interpret the standard deviation in a printed sentence: a low value
   means scores were clustered close to the mean (consistent
   performance); a high value means scores were spread out.

## Track B — Electrical/Electronic Engineering: Signal Statistics

1. Build `Statistics<double>` and feed it a series of voltage samples
   from a simulated waveform.
2. Print the mean, min, max, and standard deviation.
3. A high standard deviation here indicates a **noisy** signal; a low
   one indicates a **stable** signal — print which case applies, using
   a threshold you choose and justify in a comment.

## Track C — Biomedical Engineering: Vital Sign Statistics

1. Build `Statistics<double>` and feed it a patient's heart-rate
   readings across a monitoring session.
2. Print the mean, min, max, and standard deviation.
3. A high standard deviation here may indicate an **unstable** heart
   rhythm worth flagging for review; print a flag message when the
   standard deviation exceeds a threshold you choose and justify in a
   comment.

## Starter files

- [`generic_starter.cpp`](generic_starter.cpp)
- [`ee_starter.cpp`](ee_starter.cpp)
- [`biomedical_starter.cpp`](biomedical_starter.cpp)

## When you're done

```bash
g++ <your_chosen_starter>.cpp -o statistics_project
./statistics_project
```

```bash
git add 18-templates
git commit -m "Complete Module 18 project: generic statistics toolkit"
git push
```
