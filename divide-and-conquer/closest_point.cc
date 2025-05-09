#include <iostream>
#include <cmath>

struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

double distance(const Point& p, const Point& q)
{
    return std::sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}


double closest_pair();
