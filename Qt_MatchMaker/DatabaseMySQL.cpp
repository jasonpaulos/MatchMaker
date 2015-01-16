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

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "DatabaseMySQL.h"

DatabaseMySQL::DatabaseMySQL(const DatabaseMySQL &db):
    dbName(db.dbName),
    username(db.username),
    password(db.password),
    host(db.host),
    port(db.port)
{ }

DatabaseMySQL::DatabaseMySQL(const QString &dbName, const QString &username, const QString &password, const QString &host, int port):
    dbName(dbName),
    username(username),
    password(password),
    host(host),
    port(port)
{ }

DatabaseType DatabaseMySQL::getType() const{
    return DB_MYSQL;
}

QString DatabaseMySQL::getColumnQuery(const QString &table) const{
    return "SELECT * FROM " + table + " LIMIT 0, 0";
}

QString DatabaseMySQL::getDatabaseName() const{
    return dbName;
}

QString DatabaseMySQL::getUsername() const{
    return username;
}

QString DatabaseMySQL::getPassword() const{
    return password;
}

QString DatabaseMySQL::getHostName() const{
    return host;
}

int DatabaseMySQL::getPort() const{
    return port;
}

void DatabaseMySQL::setDatabaseName(const QString &name){
    dbName = name;
}

void DatabaseMySQL::setUsername(const QString &name){
    username = name;
}

void DatabaseMySQL::setPassword(const QString &pass){
    password = pass;
}

void DatabaseMySQL::setHostName(const QString &name){
    host = name;
}

void DatabaseMySQL::setPort(int p){
    port = p;
}

QSqlDatabase DatabaseMySQL::loadDatabase(const QString &connection){
    QSqlDatabase db(QSqlDatabase::addDatabase("QMYSQL", connection));

    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(dbName);
    db.setUserName(username);
    db.setPassword(password);

    return db;
}
