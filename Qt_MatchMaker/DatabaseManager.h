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

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <functional>
#include <QObject>
#include <QStringList>
#include <QSqlQuery>
#include "DatabaseMySQL.h"
#include "DatabaseSQLite.h"

typedef std::function<void (QString)> ErrorProcess;
typedef std::function<void (QSqlQuery*)> QueryProcess;
typedef std::function<void (QStringList)> TableProcess;

/* These help Qt pass these argument types to signals and slots.
 */
Q_DECLARE_METATYPE(ErrorProcess)
Q_DECLARE_METATYPE(QueryProcess)
Q_DECLARE_METATYPE(TableProcess)
Q_DECLARE_METATYPE(QSqlQuery)

/* This class will live on a separate thread and process everything related to SQL.
 * Why is this necessary? Because:
 *
 * 1) "A connection can only be used from within the thread that created it. Moving
 * connections between threads or creating queries from a different thread is not supported"
 * (http://qt-project.org/doc/qt-4.8/threads-modules.html)
 *
 * And
 *
 * 2) We don't want the GUI thread to get slowed down due to queries that could last
 * for several seconds, especially when working with large amounts of data.
 */
class DatabaseManager : public QObject{
    Q_OBJECT

public:
    DatabaseManager();
    ~DatabaseManager();

    /* Creates a database with the supplied connection name and Database information.
     * If there is a problem, then error will be called with a QString explanation,
     * otherwise it will be called with an empty string.
     *
     * It is important to remember that error will be called on DatabaseManager's thread.
     */
    void addConnection(const QString &connection, Database *db, const ErrorProcess &error);

    /* Removes a database connection.
     */
    void removeConnection(const QString &connection);

    /* Sends a query to the database specified by connection. The resulting QSqlQuery will be sent to
     * process. No error checking will happen, so process must handle any possible errors.
     *
     * It is important to remember that process will be called on DatabaseManager's thread.
     */
    void queryConnection(const QString &connection, const QString &query, const QueryProcess &process);

    /* Gets a list of tables present in the database specified by connection. If any problems occur,
     * error will be called, otherwise process will be called with the list of tables.
     *
     * It is important to remember that process or error (whichever gets executed) will be called on
     * DatabaseManager's thread.
     */
    void getTables(const QString &connection, const TableProcess &process, const ErrorProcess &error);

    /* The signals and slots below are used to move data between threads so that only the thread that
     * DatabaseManager lives in will be able to any database connection. No parameters are passed by
     * reference or by pointers because these functions will be called on a different thread. This works
     * out nicely for slotAddConnection because it can be overloaded for different Database types.
     */
private slots:
    void slotAddConnection(QString connection, DatabaseMySQL db, ErrorProcess error);
    void slotAddConnection(QString connection, DatabaseSQLite db, ErrorProcess error);
    void slotRemoveConnection(QString connection);
    void slotQuery(QString connection, QString query, QueryProcess process);
    void slotTables(QString connection, TableProcess process, ErrorProcess error);

signals:
    void signalAddConnection(QString connection, DatabaseMySQL db, ErrorProcess error);
    void signalAddConnection(QString connection, DatabaseSQLite db, ErrorProcess error);
    void signalRemoveConnection(QString connection);
    void signalQuery(QString connection, QString query, QueryProcess process);
    void signalTables(QString connection, TableProcess process, ErrorProcess error);

private:

    //The list of all connections created through DatabaseManager
    QStringList connections;
};

#endif // DATABASEMANAGER_H
