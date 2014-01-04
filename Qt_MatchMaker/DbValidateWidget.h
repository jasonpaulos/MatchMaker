#ifndef DBVALIDATEWIDGET_H
#define DBVALIDATEWIDGET_H

#include "StepWidget.h"

namespace Ui{
class DbValidateWidget;
}

class DbValidateWidget : public StepWidget{
    Q_OBJECT

public:
    explicit DbValidateWidget(DatabaseDialog *parent);
    ~DbValidateWidget();

    void saveData();
    void finishedQuery(bool success);

public slots:
    void slotShowError(QString error);
    void slotFillTables(QStringList tables);

signals:
    void signalShowError(QString error);
    void signalFillTables(QStringList tables);

private:
    Ui::DbValidateWidget *ui;
};

#endif // DBVALIDATEWIDGET_H
