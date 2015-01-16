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

#ifndef DBMYSQLWIDGET_H
#define DBMYSQLWIDGET_H

#include <QScopedPointer>
#include "StepWidget.h"

class DatabaseDialog;

namespace Ui{
    class DbMySQLWidget;
}

/* This widget is the 2nd step in selecting a database. Here, the user enters the
 * MySQL-specific information needed to connect to the database.
 */
class DbMySQLWidget : public StepWidget{
    Q_OBJECT

public:
    explicit DbMySQLWidget(DatabaseDialog *parent);
    ~DbMySQLWidget();

    virtual void saveData();
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
    QScopedPointer<Ui::DbMySQLWidget> ui;
};

#endif // DBMYSQLWIDGET_H
