#pragma once

namespace makersplace::school {

// Keeps only the most recent N values (a ring buffer - see Module 32 example 03).
template <typename T, int N>
class RollingWindow {
private:
    T data[N] = {};
    int start = 0;
    int count = 0;

public:
    void push(const T& value);  // TODO: define below the class
    int size() const { return count; }
    const T& operator[](int i) const { return data[(start + i) % N]; } // 0 = oldest

    // TODO (requirement 4): template <typename F> void forEach(F f) const
    //   - calls f(value) on each stored value, oldest first
};

// TODO: template <typename T, int N> void RollingWindow<T, N>::push(const T& value)

} // namespace makersplace::school
