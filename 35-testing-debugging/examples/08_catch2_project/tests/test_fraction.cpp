// Catch2 tests for Fraction. Catch2WithMain supplies main().
#include "fraction.h"

#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <stdexcept>

TEST_CASE("fractions are stored in lowest terms") {
    Fraction f(2, 4);
    REQUIRE(f.numerator() == 1);   // REQUIRE: stop this test case if it fails
    CHECK(f.denominator() == 2);   // CHECK: record a failure and carry on
}

TEST_CASE("the sign always lives in the numerator") {
    Fraction f(3, -6);
    CHECK(f.numerator() == -1);
    CHECK(f.denominator() == 2);
}

TEST_CASE("a zero denominator is rejected") {
    REQUIRE_THROWS_AS(Fraction(1, 0), std::invalid_argument);
}

TEST_CASE("adding fractions") {
    Fraction half(1, 2); // each SECTION below starts again from here, with a fresh half

    SECTION("adding a third") {
        CHECK(half + Fraction(1, 3) == Fraction(5, 6));
    }
    SECTION("adding a negative") {
        CHECK(half + Fraction(-1, 2) == Fraction(0));
    }
    SECTION("+= changes the left-hand side") {
        half += Fraction(1, 2);
        CHECK(half == Fraction(1));
    }
}

TEST_CASE("multiplying fractions") {
    CHECK(Fraction(2, 3) * Fraction(3, 4) == Fraction(1, 2));
    CHECK(Fraction(5) * Fraction(1, 5) == Fraction(1));
}

TEST_CASE("comparing fractions") {
    CHECK(Fraction(1, 3) < Fraction(1, 2));
    CHECK(Fraction(2, 4) == Fraction(1, 2));
    CHECK(Fraction(-1, 2) < Fraction(0));
}

TEST_CASE("printing fractions") {
    std::ostringstream out;
    out << Fraction(3, 4) << " " << Fraction(4, 2);
    CHECK(out.str() == "3/4 2");
}
