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
#include <algorithm>
#include <cassert>
#include "MathVector.h"

template <typename E>
MathVector<E>::MathVector(unsigned int dimensions):
    elements(dimensions, 0)
{ }

template <typename E>
MathVector<E>::MathVector(const std::vector<E> &v):
    elements(v)
{ }

template <typename E>
MathVector<E>::MathVector(std::vector<E> &&v):
    elements(std::move(v))
{ }

template <typename E>
MathVector<E>::MathVector(const MathVector<E> &v):
    elements(v.elements)
{ }

template <typename E>
MathVector<E>::MathVector(MathVector<E> &&v):
    elements(std::move(v.elements))
{ }

template <typename E>
unsigned int MathVector<E>::getDimensions() const{
    return static_cast<unsigned int>(elements.size());
}

template <typename E>
E MathVector<E>::getMagnitude() const{
    return sqrt(getMagnitudeSquared());
}

template <typename E>
E MathVector<E>::getMagnitudeSquared() const{
    float rawMag = 0.0F;

    for(E e : elements){
        rawMag += e * e;
    }

    return rawMag;
}

template <typename E>
MathVector<E> MathVector<E>::operator+(const MathVector<E> &v) const{
    unsigned int dimensions = getDimensions();
    assert(dimensions == v.getDimensions());

    MathVector<E> sum(dimensions);
    std::transform(elements.begin(), elements.end(), v.elements.begin(), sum.elements.begin(), std::plus<E>());

    return sum;
}

template <typename E>
MathVector<E> MathVector<E>::operator-(const MathVector<E> &v) const{
    unsigned int dimensions = getDimensions();
    assert(dimensions == v.getDimensions());

    MathVector<E> diff(dimensions);
    std::transform(elements.begin(), elements.end(), v.elements.begin(), diff.elements.begin(), std::minus<E>());

    return diff;
}

template class MathVector<float>;

