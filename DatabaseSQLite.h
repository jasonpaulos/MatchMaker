#ifndef DATABASESQLITE_H
#define DATABASESQLITE_H

#include <QMetaType>
#include <QDir>
#include "Database.h"

class DatabaseSQLite : public Database{
public:
    DatabaseSQLite(const DatabaseSQLite &db);
    DatabaseSQLite(const QString &dbName = QDir::homePath());

    DatabaseType getType() const;
    QString getColumnQuery(const QString &table) const;
    QString getDatabaseName() const;
    void setDatabaseName(const QString &name);
    QSqlDatabase loadDatabase(const QString &connection);
private:
    QString dbName;
};

Q_DECLARE_METATYPE(DatabaseSQLite)

#endif // DATABASESQLITE_H
