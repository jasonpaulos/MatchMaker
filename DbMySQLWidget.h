#ifndef DBMYSQLWIDGET_H
#define DBMYSQLWIDGET_H

#include "StepWidget.h"

class DatabaseDialog;

namespace Ui{
class DbMySQLWidget;
}

class DbMySQLWidget : public StepWidget{
    Q_OBJECT

public:
    explicit DbMySQLWidget(DatabaseDialog *parent);
    ~DbMySQLWidget();

    void saveData();
    int getPort() const;
    QString getHostName() const;
    QString getDatabaseName() const;
    QString getUsername() const;
    QString getPassword() const;
    void setPort(int p);
    void setHostName(const QString &name);
    void setDatabaseName(const QString &name);
    void setUsername(const QString &name);
    void setPassword(const QString &pass);

private:
    Ui::DbMySQLWidget *ui;
};

#endif // DBMYSQLWIDGET_H
