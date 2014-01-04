#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>

enum DatabaseType{
    DB_MYSQL = 0,
    DB_SQLITE = 1
};

class Database{
public:
    virtual DatabaseType getType() const = 0;
    virtual QString getColumnQuery(const QString &table) const = 0;
    virtual QString getDatabaseName() const = 0;
    virtual QSqlDatabase loadDatabase(const QString &connection) = 0;
    virtual ~Database(){ }
};

#endif // DATABASE_H
