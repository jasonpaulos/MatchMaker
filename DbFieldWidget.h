#ifndef DBFIELDWIDGET_H
#define DBFIELDWIDGET_H

#include <QVector>
#include <QSqlQuery>
#include "StepWidget.h"

class QCheckBox;

namespace Ui{
class DbFieldWidget;
}

class DbFieldWidget : public StepWidget{
    Q_OBJECT

public:
    explicit DbFieldWidget(DatabaseDialog *parent);
    ~DbFieldWidget();

    void saveData();
    bool canFinish();
    void showError(const QString &error);

public slots:
    void slotProcessQuery(QSqlQuery query);

signals:
    void signalProcessQuery(QSqlQuery query);

private slots:
    void on_questionSelect_clicked();
    void on_questionDeselect_clicked();

private:
    QVector<QCheckBox*> questionFields;
    Ui::DbFieldWidget *ui;
};

#endif // DBFIELDWIDGET_H
