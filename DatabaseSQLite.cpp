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
