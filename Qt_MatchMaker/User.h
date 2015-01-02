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

#ifndef USER_H
#define USER_H

#include <map>
#include <QString>
#include "MathVector.h"

/* This class represents a user and his or her answers. The answers are stored
 * as a Point because the matching algorithm we use is centered around linear
 * algebra. The smaller the "distance" between two points from different Users are,
 * the more likely those users will be matched up. MatchEngine uses this theory
 * to calculate the matches based on the "distance" between Users' answers.
 */
class User{
public:
    explicit User(const QString &name, Gender gender, unsigned int dimensions);

    /* This should only be called if a grade field is present in DatabaseSetup,
     * otherwise, the return value will be undefined.
     */
    Grade getGrade() const;

    QString name;
    Gender gender;
    MathVector answers;
    std::map<float, const User*> matches;
};

#endif // USER_H
