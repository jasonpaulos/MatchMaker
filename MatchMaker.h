#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include <QThread>
#include <QScopedPointer>
#include "Database.h"
#include "DatabaseSetup.h"
#include "DatabaseManager.h"
#include "User.h"

class MatchMaker{
public:
    MatchMaker();
    ~MatchMaker();

    QThread *dbThread;
    QScopedPointer<DatabaseManager> dbManager;
    DatabaseSetup dbSetup;
    QScopedPointer<Database> db;
    std::vector<User> male, female;

    static MatchMaker *instance;
};

#endif // MATCHMAKER_H
