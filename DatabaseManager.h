#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <functional>
#include <QObject>
#include <QStringList>
#include <QSqlQuery>
#include "DatabaseMySQL.h"
#include "DatabaseSQLite.h"

typedef std::function<void (QString)> ErrorProcess;
typedef std::function<void (QSqlQuery)> QueryProcess;
typedef std::function<void (QStringList)> TableProcess;

Q_DECLARE_METATYPE(ErrorProcess)
Q_DECLARE_METATYPE(QueryProcess)
Q_DECLARE_METATYPE(TableProcess)
Q_DECLARE_METATYPE(QSqlQuery)

class DatabaseManager : public QObject{
    Q_OBJECT

public:
    DatabaseManager();
    ~DatabaseManager();

    void addConnection(const QString &connection, Database *db, const ErrorProcess &error);
    void removeConnection(const QString &connection);
    void queryConnection(const QString &connection, const QString &query, const QueryProcess &process);
    void getTables(const QString &connection, const TableProcess &process, const ErrorProcess &error);

public slots:
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
    QStringList connections;
};

#endif // DATABASEMANAGER_H
