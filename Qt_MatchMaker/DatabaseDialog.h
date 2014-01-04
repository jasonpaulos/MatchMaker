#ifndef DATABASEDIALOG_H
#define DATABASEDIALOG_H

#include <QScopedPointer>
#include <QDialog>
#include "StepWidget.h"
#include "Database.h"
#include "DatabaseSetup.h"

namespace Ui{
class DatabaseDialog;
}

class DatabaseDialog : public QDialog{
    Q_OBJECT

public:
    enum State{
        STATE_NONE,
        STATE_CHOOSE,
        STATE_MYSQL,
        STATE_SQLITE,
        STATE_VALIDATE,
        STATE_FIELD
    };

    enum Button{
        BUTTON_BACK,
        BUTTON_NEXT,
        BUTTON_FINISH
    };

    explicit DatabaseDialog(bool *success, DatabaseSetup *dbSetup, QScopedPointer<Database> &db, QWidget *parent = nullptr);
    ~DatabaseDialog();

    void setState(State state);
    bool isButtonEnabled(Button button) const;
    void setButtonState(Button button, bool enabled);
    void setDefaultButton(Button button);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_cancelButton_clicked();
    void on_backButton_clicked();
    void on_nextButton_clicked();
    void on_finishButton_clicked();

public:
    bool *success;
    QScopedPointer<Database> &db;
    DatabaseSetup *dbSetup;
    QRect widgetGeometry;
    QString widgetName;
    State currentState;
    StepWidget *currentWidget;

private:
    Ui::DatabaseDialog *ui;
};

#endif // DATABASEDIALOG_H
