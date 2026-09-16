#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> words = {"cat", "dog", "cat", "bird", "dog", "cat"};

    std::map<std::string, int> wordCounts;
    for (const std::string& word : words) {
        wordCounts[word]++;
    }

    for (const auto& pair : wordCounts) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::set<std::string> uniqueWords;
    for (const std::string& word : words) {
        uniqueWords.insert(word);
    }
    std::cout << "Total words: " << words.size() << std::endl;
    std::cout << "Unique words: " << uniqueWords.size() << std::endl;

    return 0;
}
