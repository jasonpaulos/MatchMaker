#ifndef STEPWIDGET_H
#define STEPWIDGET_H

#include <QWidget>

class DatabaseDialog;

class StepWidget : public QWidget{
    Q_OBJECT

public:
    explicit StepWidget(DatabaseDialog *parent);

    virtual void saveData() = 0;
    virtual bool canFinish();

protected:
    DatabaseDialog *dialog;
};

#endif // STEPWIDGET_H
