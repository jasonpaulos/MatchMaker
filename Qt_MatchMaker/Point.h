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

#ifndef POINT_H
#define POINT_H

#include <vector>
#include "Environment.h"

/* A basic linear algebra point class that can be initialized to any number of
 * dimensions. See User.h for implementation.
 */
class Point{
public:
    explicit Point(unsigned int dimensions);
    explicit Point(const std::vector<byte> &v);
    Point(const Point &p);

    unsigned int getDimensions() const;

    /* Calculates the distance between two points using linear algebra.
     */
    float getDistance(const Point &p) const;

    /* Calculates the squared distance between two points using linear
     * algebra. This method doesn't call sqrt() like the above one,
     * so it is faster.
     */
    float getDistanceSquared(const Point &p) const;

    std::vector<byte> elements;
};

#endif // POINT_H
