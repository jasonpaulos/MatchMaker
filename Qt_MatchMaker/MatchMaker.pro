#-------------------------------------------------
#
# Project created by QtCreator 2013-12-23T16:58:29
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

TARGET = MatchMaker
TEMPLATE = app

win32 {
    RC_FILE += resource.rc
}

# Mac OSX icons
unix {
    ICON = icon.icns
}

SOURCES +=  main.cpp\
    MainWindow.cpp \
    DatabaseDialog.cpp \
    DbChooseWidget.cpp \
    DbSQLiteWidget.cpp \
    DbMySQLWidget.cpp \
    DbValidateWidget.cpp \
    DatabaseMySQL.cpp \
    DatabaseSQLite.cpp \
    DatabaseSetup.cpp \
    StepWidget.cpp \
    User.cpp \
    MatchMaker.cpp \
    DbFieldWidget.cpp \
    DatabaseManager.cpp \
    MatchEngine.cpp \
    PrintEngine.cpp \
    MathVector.cpp

HEADERS  += MainWindow.h \
    DatabaseDialog.h \
    DbChooseWidget.h \
    Database.h \
    DbSQLiteWidget.h \
    DbMySQLWidget.h \
    DbValidateWidget.h \
    DatabaseMySQL.h \
    DatabaseSQLite.h \
    DatabaseSetup.h \
    StepWidget.h \
    User.h \
    Environment.h \
    MatchMaker.h \
    DbFieldWidget.h \
    DatabaseManager.h \
    MatchEngine.h \
    PrintEngine.h \
    MathVector.h

FORMS    += MainWindow.ui \
    DatabaseDialog.ui \
    DbChooseWidget.ui \
    DbSQLiteWidget.ui \
    DbMySQLWidget.ui \
    DbValidateWidget.ui \
    DbFieldWidget.ui
