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

#ifndef DATABASESETUP_H
#define DATABASESETUP_H

#include <QStringList>

/* This class holds the table and field names of a database that correspond to
 * required information. For example, the QString gender will hold the field
 * name in a database which contains users' genders.
 */
class DatabaseSetup{
public:
    explicit DatabaseSetup(const QString &table = "",
                           const QString &gender = "",
                           const QString &grade = "",
                           const QString &first = "",
                           const QString &middle = "",
                           const QString &last = "");

    bool hasFirstName() const;
    bool hasMiddleName() const;
    bool hasLastName() const;
    bool hasGrade() const;
    const QString& getTable() const;
    const QString& getGender() const;
    const QString& getGrade() const;
    const QString& getFirstName() const;
    const QString& getMiddleName() const;
    const QString& getLastName() const;
    const QStringList& getQuestions() const;
    void setTable(const QString &t);
    void setGender(const QString &g);
    void setGrade(const QString &g);
    void setFirstName(const QString &name);
    void setMiddleName(const QString &name);
    void setLastName(const QString &name);
    void addQuestion(const QString &name);
    void clearQuestions();

private:
    QString table, gender, grade, firstName, middleName, lastName;
    QStringList questions;
};

#endif // DATABASESETUP_H
