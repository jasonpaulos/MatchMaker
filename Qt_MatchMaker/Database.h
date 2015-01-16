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

#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>

enum DatabaseType{
    DB_MYSQL = 0,
    DB_SQLITE = 1
};

/* This class represents a database and should contain all the necessary information
 * needed to create a QSqlDatabase.
 */
class Database{
public:
    virtual DatabaseType getType() const = 0;

    /* Returns a query that, when sent to a datbase, should return a list of all columns
     * in a table. This function exists because different databases require different queries to
     * obtain a list of columns.
     */
    virtual QString getColumnQuery(const QString &table) const = 0;

    virtual QString getDatabaseName() const = 0;

    /* Returns a QSqlDatabase with the specified connection that uses the information present
     * in this object. This function should only be called in DatabaseManager's thread.
     */
    virtual QSqlDatabase loadDatabase(const QString &connection) = 0;

    virtual ~Database(){ }
};

#endif // DATABASE_H
