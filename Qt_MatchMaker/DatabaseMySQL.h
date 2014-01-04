#ifndef DATABASEMYSQL_H
#define DATABASEMYSQL_H

#include <QMetaType>
#include "Database.h"

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

Q_DECLARE_METATYPE(DatabaseMySQL)

#endif // DATABASEMYSQL_H
