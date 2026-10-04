// throw; rethrows the SAME exception (keeping its real type).
// Translating turns a low-level exception into one from OUR hierarchy,
// with useful context.
#include <iostream>
#include <stdexcept>
#include <string>

class SchoolError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class CorruptRecordError : public SchoolError {
public:
    using SchoolError::SchoolError;
};

double parseScore(const std::string& text) {
    return std::stod(text); // throws std::invalid_argument for "abc"
}

// Low level -> high level: TRANSLATE.
double loadScore(const std::string& studentId, const std::string& rawField) {
    try {
        return parseScore(rawField);
    } catch (const std::invalid_argument& e) {
        throw CorruptRecordError("record for " + studentId + " is corrupted (score field '" + rawField + "')");
    }
}

// Middle layer: LOG and RETHROW, without handling.
double loadWithLogging(const std::string& studentId, const std::string& rawField) {
    try {
        return loadScore(studentId, rawField);
    } catch (const std::exception& e) {
        std::cout << "  [log] problem while loading " << studentId << std::endl;
        throw; // the SAME CorruptRecordError continues upwards - not a sliced copy
    }
}

int main() {
    const std::string records[][2] = {{"MP-001", "84.5"}, {"MP-002", "abc"}, {"MP-003", "71"}};

    for (const auto& r : records) {
        try {
            double score = loadWithLogging(r[0], r[1]);
            std::cout << "  " << r[0] << ": " << score << std::endl;
        } catch (const CorruptRecordError& e) { // the precise type survived the rethrow
            std::cout << "  skipped: " << e.what() << std::endl;
        }
    }
    return 0;
}
