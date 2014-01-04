#include <cmath>
#include <cassert>
#include "Point.h"

Point::Point(unsigned int dimensions):
    elements(dimensions, 0)
{ }

Point::Point(const std::vector<byte> &v):
    elements(v)
{ }

Point::Point(const Point &p):
    elements(p.elements)
{ }


unsigned int Point::getDimensions() const{
    return (unsigned int)elements.size();
}

float Point::getDistance(const Point &p) const{
    return sqrt(getDistanceSquared(p));
}

float Point::getDistanceSquared(const Point &p) const{
    unsigned int dimensions = getDimensions();
    assert(dimensions == p.getDimensions());

    float rawDistance = 0.0F;

    for(unsigned int i = 0; i < dimensions; ++i){
        rawDistance += pow(elements.at(i) - p.elements.at(i), 2);
    }

    return rawDistance;
}
