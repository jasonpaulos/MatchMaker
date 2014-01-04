#include <QSqlError>
#include <QSqlDatabase>
#include <QFileInfo>
#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(){
    qRegisterMetaType<ErrorProcess>();
    qRegisterMetaType<QueryProcess>();
    qRegisterMetaType<TableProcess>();
    qRegisterMetaType<DatabaseMySQL>();
    qRegisterMetaType<DatabaseSQLite>();
    qRegisterMetaType<QSqlQuery>();

    connect(this, SIGNAL(signalAddConnection(QString, DatabaseMySQL, ErrorProcess)), this, SLOT(slotAddConnection(QString, DatabaseMySQL, ErrorProcess)));
    connect(this, SIGNAL(signalAddConnection(QString, DatabaseSQLite, ErrorProcess)), this, SLOT(slotAddConnection(QString, DatabaseSQLite, ErrorProcess)));
    connect(this, SIGNAL(signalRemoveConnection(QString)), this, SLOT(slotRemoveConnection(QString)));
    connect(this, SIGNAL(signalQuery(QString, QString, QueryProcess)), this, SLOT(slotQuery(QString, QString, QueryProcess)));
    connect(this, SIGNAL(signalTables(QString,TableProcess,ErrorProcess)), this, SLOT(slotTables(QString,TableProcess,ErrorProcess)));
}

DatabaseManager::~DatabaseManager(){
    for(auto i = connections.begin(); i != connections.end(); ++i){
        QSqlDatabase::removeDatabase(*i);
    }
}

void DatabaseManager::addConnection(const QString &connection, Database *db, const ErrorProcess &error){
    switch(db->getType()){
    case DB_MYSQL:
        emit signalAddConnection(connection, *static_cast<DatabaseMySQL*>(db), error);
        break;
    case DB_SQLITE:
        emit signalAddConnection(connection, *static_cast<DatabaseSQLite*>(db), error);
        break;
    default:
        error("Database type was not recognized");
    }
}

void DatabaseManager::removeConnection(const QString &connection){
    emit signalRemoveConnection(connection);
}

void DatabaseManager::queryConnection(const QString &connection, const QString &query, const QueryProcess &process){
    emit signalQuery(connection, query, process);
}

void DatabaseManager::getTables(const QString &connection, const TableProcess &process, const ErrorProcess &error){
    emit signalTables(connection, process, error);
}

void DatabaseManager::slotAddConnection(QString connection, DatabaseMySQL db, ErrorProcess error){
    QSqlDatabase database(db.loadDatabase(connection));

    if(database.lastError().isValid()){
        QString message(database.lastError().text());

        if(db.getHostName() == "localhost"){
            message += "\n\nTip: Try using 127.0.0.1 instead of localhost";
        }

        error(message);
    }else{
        connections.push_back(connection);
        error("");
    }
}

void DatabaseManager::slotAddConnection(QString connection, DatabaseSQLite db, ErrorProcess error){
    QString path(db.getDatabaseName());
    QFileInfo file(path);

    if(file.exists() && file.isFile()){
        QSqlDatabase database(db.loadDatabase(connection));

        if(database.lastError().isValid()){
            error(database.lastError().text());
        }else{
            connections.push_back(connection);
            error("");
        }
    }else{
        error("Cannot find file at " + path);
    }
}

void DatabaseManager::slotRemoveConnection(QString connection){
    QSqlDatabase::removeDatabase(connection);

    if(connections.count(connection) > 0){
        connections.removeAll(connection);
    }
}

void DatabaseManager::slotQuery(QString connection, QString query, QueryProcess process){
    QSqlQuery databaseQuery(QSqlDatabase::database(connection));

    databaseQuery.exec(query);

    process(databaseQuery);
}

void DatabaseManager::slotTables(QString connection, TableProcess process, ErrorProcess error){
    QSqlDatabase database(QSqlDatabase::database(connection));

    if(database.lastError().isValid()){
        error(database.lastError().text());
    }else{
        QStringList tables(database.tables());

        if(database.lastError().isValid()){
            error(database.lastError().text());
        }else{
            process(tables);
        }
    }
}
