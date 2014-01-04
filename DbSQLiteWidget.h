#ifndef DBSQLITEWIDGET_H
#define DBSQLITEWIDGET_H

#include "StepWidget.h"

class DatabaseDialog;

namespace Ui{
class DbSQLiteWidget;
}

class DbSQLiteWidget : public StepWidget{
    Q_OBJECT

public:
    explicit DbSQLiteWidget(DatabaseDialog *parent);
    ~DbSQLiteWidget();

    void saveData();
    QString getDatabaseName() const;
    void setDatabaseName(const QString &name);

private slots:
    void on_browseButton_clicked();

private:
    Ui::DbSQLiteWidget *ui;
};

#endif // DBSQLITEWIDGET_H
