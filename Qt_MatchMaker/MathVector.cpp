/* Copyright (c) 2014 Jason Paulos
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <cmath>
#include <cassert>
#include "MathVector.h"

MathVector::MathVector(unsigned int dimensions):
    elements(dimensions, 0)
{ }

MathVector::MathVector(const std::vector<byte> &v):
    elements(v)
{ }

MathVector::MathVector(const MathVector &v):
    elements(v.elements)
{ }


unsigned int MathVector::getDimensions() const{
    return static_cast<unsigned int>(elements.size());
}

float MathVector::getDistance(const MathVector &v) const{
    return sqrt(getDistanceSquared(v));
}

float MathVector::getDistanceSquared(const MathVector &v) const{
    unsigned int dimensions = getDimensions();
    assert(dimensions == v.getDimensions());

    float rawDistance = 0.0F;

    for(unsigned int i = 0; i < dimensions; ++i){
        rawDistance += pow(elements.at(i) - v.elements.at(i), 2);
    }

    return rawDistance;
}
