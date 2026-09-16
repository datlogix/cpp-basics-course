// Exercise 1: STL Containers & Iterators
//
// TODO 1: Build a std::map<std::string, int> called wordCounts.
// TODO 2: Given the words vector below, loop over it and count how many
//         times each word appears in wordCounts (hint:
//         wordCounts[word]++ works even for a brand-new key, since
//         map's [] default-constructs missing keys to 0 for int).
// TODO 3: Loop over wordCounts (sorted by key automatically) and print
//         "<word>: <count>" for each.
// TODO 4: Build a std::set<std::string> called uniqueWords from the
//         same words vector (insert each one) and print its size,
//         proving it's smaller than words.size() if there are repeats.
//
// Compile and run:
//   g++ exercise1.cpp -o exercise1
//   ./exercise1
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> words = {"cat", "dog", "cat", "bird", "dog", "cat"};

    // Your code here

    return 0;
}
