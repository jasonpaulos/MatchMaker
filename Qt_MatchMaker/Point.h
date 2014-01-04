#ifndef POINT_H
#define POINT_H

#include <vector>
#include "Environment.h"

class Point{
public:
    explicit Point(unsigned int dimensions);
    explicit Point(const std::vector<byte> &v);
    Point(const Point &p);

    unsigned int getDimensions() const;
    float getDistance(const Point &p) const;
    float getDistanceSquared(const Point &p) const;

    std::vector<byte> elements;
};

#endif // POINT_H
