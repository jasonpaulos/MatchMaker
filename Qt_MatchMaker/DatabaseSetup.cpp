/* Copyright (c) 2015 Jason Paulos
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

#include "DatabaseSetup.h"

DatabaseSetup::DatabaseSetup(const QString &table,
                             const QString &gender,
                             const QString &grade,
                             const QString &first,
                             const QString &middle,
                             const QString &last):
    table(table),
    gender(gender),
    grade(grade),
    firstName(first),
    middleName(middle),
    lastName(last)
{ }

bool DatabaseSetup::hasFirstName() const{
    return !firstName.isEmpty();
}

bool DatabaseSetup::hasMiddleName() const{
    return !middleName.isEmpty();
}

bool DatabaseSetup::hasLastName() const{
    return !lastName.isEmpty();
}

bool DatabaseSetup::hasGrade() const{
    return !grade.isEmpty();
}

const QString& DatabaseSetup::getTable() const{
    return table;
}

const QString& DatabaseSetup::getGender() const{
    return gender;
}

const QString& DatabaseSetup::getGrade() const{
    return grade;
}

const QString& DatabaseSetup::getFirstName() const{
    return firstName;
}

const QString& DatabaseSetup::getMiddleName() const{
    return middleName;
}

const QString& DatabaseSetup::getLastName() const{
    return lastName;
}

const QStringList& DatabaseSetup::getQuestions() const{
    return questions;
}

void DatabaseSetup::setTable(const QString &t){
    table = t;
}

void DatabaseSetup::setGender(const QString &g){
    gender = g;
}

void DatabaseSetup::setGrade(const QString &g){
    grade = g;
}

void DatabaseSetup::setFirstName(const QString &name){
    firstName = name;
}

void DatabaseSetup::setMiddleName(const QString &name){
    middleName = name;
}

void DatabaseSetup::setLastName(const QString &name){
    lastName = name;
}

void DatabaseSetup::addQuestion(const QString &name){
    questions << name;
}

void DatabaseSetup::clearQuestions(){
    questions.clear();
}
