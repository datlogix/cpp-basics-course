// point.h - the HEADER: WHAT a Point offers (declarations only).
#pragma once

class Point {
private:
    double x;
    double y;

public:
    Point(double xValue, double yValue);
    double distanceTo(const Point& other) const;
    void print() const;
};
