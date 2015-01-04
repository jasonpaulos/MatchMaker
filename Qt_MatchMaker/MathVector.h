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

#ifndef MATHVECTOR_H
#define MATHVECTOR_H

#include <vector>
#include "Environment.h"

/* A basic math vector class that can be initialized to any number of
 * dimensions. See User.h for implementation.
 */
template <typename E>
class MathVector{
public:
    explicit MathVector(unsigned int dimensions);
    explicit MathVector(const std::vector<E> &v);
    explicit MathVector(std::vector<E> &&v);
    MathVector(const MathVector<E> &v);
    MathVector(MathVector<E> &&v);

    unsigned int getDimensions() const;

    /* Calculates the magnitude of the vector
     */
    float getMagnitude() const;

    /* Calculates the squared magnitude of the vector.
     * This method doesn't call sqrt() like the one above, so it is faster.
     */
    float getMagnitudeSquared() const;

    MathVector operator+(const MathVector<E> &v) const;
    MathVector operator-(const MathVector<E> &v) const;

    std::vector<E> elements;
};

typedef MathVector<short> MathVec;

#endif // MATHVECTOR_H
