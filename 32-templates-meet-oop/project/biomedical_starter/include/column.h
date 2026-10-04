#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace makersplace::clinic {

// The abstract base: lets columns of DIFFERENT types share one interface.
class Column {
public:
    virtual ~Column() = default;
    virtual std::string heading() const = 0;
    virtual int rows() const = 0;
    virtual void printCell(std::ostream& os, int row) const = 0;
};

// TODO (requirement 5): template <typename T> class ChartColumn : public Column
//   - a heading and a std::vector<T> of cells
//   - void add(const T& cell)
//   - overrides heading(), rows(), printCell()

// Prints any set of columns as a table - it never needs to know their types.
// 'inline' allows a normal function's body to live in a header that several
// .cpp files include, without a "multiple definition" linker error (Module 22).
inline void printTable(const std::vector<std::unique_ptr<Column>>& columns) {
    if (columns.empty()) {
        return;
    }
    for (const auto& c : columns) {
        std::cout << c->heading() << "\t";
    }
    std::cout << std::endl;
    for (int r = 0; r < columns[0]->rows(); r++) {
        for (const auto& c : columns) {
            c->printCell(std::cout, r);
            std::cout << "\t";
        }
        std::cout << std::endl;
    }
}

} // namespace makersplace::clinic
