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

#include "DatabaseSQLite.h"

DatabaseSQLite::DatabaseSQLite(const DatabaseSQLite &db):
    dbName(db.dbName)
{ }

DatabaseSQLite::DatabaseSQLite(const QString &dbName):
    dbName(dbName)
{ }

DatabaseType DatabaseSQLite::getType() const{
    return DB_SQLITE;
}

QString DatabaseSQLite::getColumnQuery(const QString &table) const{
    return "SELECT * FROM " + table + " LIMIT 0, 0";
}

QString DatabaseSQLite::getDatabaseName() const{
    return dbName;
}

void DatabaseSQLite::setDatabaseName(const QString &name){
    dbName = name;
}

QSqlDatabase DatabaseSQLite::loadDatabase(const QString &connection){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connection);

    db.setDatabaseName(dbName);

    return db;
}
