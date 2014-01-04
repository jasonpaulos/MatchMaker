/* Copyright (c) 2014 Jason Paulos
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

#ifndef DBFIELDWIDGET_H
#define DBFIELDWIDGET_H

#include <QScopedPointer>
#include <QVector>
#include <QSqlQuery>
#include "StepWidget.h"

class QCheckBox;

namespace Ui{
    class DbFieldWidget;
}

/* This widget is the 4th and last step in selecting a databse. Here, the user will
 * specify which fields contain what information, such as names, genders, etc.
 */
class DbFieldWidget : public StepWidget{
    Q_OBJECT

public:
    explicit DbFieldWidget(DatabaseDialog *parent);
    ~DbFieldWidget();

    virtual void saveData();
    virtual bool canFinish();
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
    QScopedPointer<Ui::DbFieldWidget> ui;
};

#endif // DBFIELDWIDGET_H
