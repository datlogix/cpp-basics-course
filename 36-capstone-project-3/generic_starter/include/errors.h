#pragma once

#include <stdexcept>
#include <string>

namespace makersplace::school {

// The root of YOUR exception hierarchy (Stage 3). Derive every
// exception your system throws from this.
class SchoolError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// Thrown (by your loading code) when a line of a data file can't be parsed.
class CorruptRecordError : public SchoolError {
private:
    std::string file;
    int lineNumber;

public:
    CorruptRecordError(std::string f, int line, std::string problem)
        : SchoolError(f + " line " + std::to_string(line) + ": " + problem), file(f), lineNumber(line) {}
    std::string getFile() const { return file; }
    int getLine() const { return lineNumber; }
};

// TODO (Stage 3): the rest of your hierarchy - at least one more
// exception that carries data.

} // namespace makersplace::school
