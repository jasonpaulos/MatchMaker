#ifndef DBCHOOSEWIDGET_H
#define DBCHOOSEWIDGET_H

#include "StepWidget.h"
#include "Database.h"

namespace Ui{
class DbChooseWidget;
}

class DbChooseWidget : public StepWidget{
    Q_OBJECT

public:
    explicit DbChooseWidget(DatabaseDialog *parent);
    ~DbChooseWidget();

    void saveData();
    DatabaseType getDatabase() const;
    void setDatabase(DatabaseType type);

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::DbChooseWidget *ui;
};

#endif // DBCHOOSEWIDGET_H
