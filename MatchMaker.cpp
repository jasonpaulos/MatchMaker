#include "MatchMaker.h"

MatchMaker *MatchMaker::instance = nullptr;

MatchMaker::MatchMaker():
    dbThread(new QThread()),
    dbManager(new DatabaseManager()),
    db(nullptr)
{
    dbManager->moveToThread(dbThread);

    dbThread->start();
}

MatchMaker::~MatchMaker(){
    dbThread->quit();
    dbThread->deleteLater();
}
