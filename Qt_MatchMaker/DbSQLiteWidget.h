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

#ifndef DBSQLITEWIDGET_H
#define DBSQLITEWIDGET_H

#include <QScopedPointer>
#include <QFileDialog>
#include "StepWidget.h"

class DatabaseDialog;

namespace Ui{
    class DbSQLiteWidget;
}

/* This widget is the 2nd step in selecting a database. Here, the user enters the
 * SQLite-specific information needed to connect to the database.
 */
class DbSQLiteWidget : public StepWidget{
    Q_OBJECT

public:
    explicit DbSQLiteWidget(DatabaseDialog *parent);
    ~DbSQLiteWidget();

    virtual void saveData();
    QString getDatabaseName() const;
    void setDatabaseName(const QString &name);

private slots:
    void on_browseButton_clicked();

public slots:
    void fileDialogSelected(const QString &file);
    void fileDialogCancelled();

private:
    QFileDialog *fileDialog;
    QScopedPointer<Ui::DbSQLiteWidget> ui;
};

#endif // DBSQLITEWIDGET_H
