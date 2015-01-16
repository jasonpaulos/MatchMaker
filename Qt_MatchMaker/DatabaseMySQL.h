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

#ifndef DATABASEMYSQL_H
#define DATABASEMYSQL_H

#include <QMetaType>
#include "Database.h"

/* The MySQL Database implementation.
 */
class DatabaseMySQL : public Database{
public:
    DatabaseMySQL(const DatabaseMySQL &db);

    DatabaseMySQL(
            const QString &dbName = "",
            const QString &username = "",
            const QString &password = "",
            const QString &host = "",
            int port = 3306
    );

    DatabaseType getType() const;
    QString getColumnQuery(const QString &table) const;
    QString getDatabaseName() const;
    QString getUsername() const;
    QString getPassword() const;
    QString getHostName() const;
    int getPort() const;
    void setDatabaseName(const QString &name);
    void setUsername(const QString &name);
    void setPassword(const QString &pass);
    void setHostName(const QString &name);
    void setPort(int p);
    QSqlDatabase loadDatabase(const QString &connection);

protected:
    int port;
    QString host, dbName, username, password;
};

/* This helps Qt pass DatabaseMySQL to signals and slots.
 */
Q_DECLARE_METATYPE(DatabaseMySQL)

#endif // DATABASEMYSQL_H
