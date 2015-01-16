/* Copyright (c) 2015 Jason Paulos
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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

/* This dialog is responsible for display all of the steps necessary to select
 * a database to work with and to specifiy its fields.
 */
class DatabaseDialog : public QDialog{
    Q_OBJECT

public:

    /* This enum represents which StepWidget is being displayed by the dialog.
     */
    enum State{
        STATE_NONE,
        STATE_CHOOSE,
        STATE_MYSQL,
        STATE_SQLITE,
        STATE_VALIDATE,
        STATE_FIELD
    };

    /* This enum represents the 3 buttons that will be displayed under the current
     * StepWidget that will be used to move between widgets and to cancel database
     * selection.
     */
    enum Button{
        BUTTON_BACK,
        BUTTON_NEXT,
        BUTTON_FINISH
    };

    explicit DatabaseDialog(QWidget *parent = nullptr);
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

signals:
    void finished(bool success, QScopedPointer<Database> &db, DatabaseSetup &dbSetup);

public:
    bool success;
    QScopedPointer<Database> db;
    DatabaseSetup dbSetup;
    QRect widgetGeometry;
    QString widgetName;
    State currentState;
    StepWidget *currentWidget;

private:
    QScopedPointer<Ui::DatabaseDialog> ui;
};

#endif // DATABASEDIALOG_H
