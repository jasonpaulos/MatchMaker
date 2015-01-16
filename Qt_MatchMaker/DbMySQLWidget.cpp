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

#include "DatabaseDialog.h"
#include "DatabaseMySQL.h"
#include "DbMySQLWidget.h"
#include "ui_DbMySQLWidget.h"

DbMySQLWidget::DbMySQLWidget(DatabaseDialog *parent):
    StepWidget(parent),
    ui(new Ui::DbMySQLWidget())
{
    ui->setupUi(this);

    DatabaseMySQL *db = dynamic_cast<DatabaseMySQL*>(dialog->db.data());
    if(db){
        setPort(db->getPort());
        setHostName(db->getHostName());
        setDatabaseName(db->getDatabaseName());
        setUsername(db->getUsername());
        setPassword(db->getPassword());
    }

    dialog->setButtonState(DatabaseDialog::BUTTON_BACK, true);
    dialog->setButtonState(DatabaseDialog::BUTTON_NEXT, true);
    dialog->setButtonState(DatabaseDialog::BUTTON_FINISH, false);
    dialog->setDefaultButton(DatabaseDialog::BUTTON_NEXT);
}

DbMySQLWidget::~DbMySQLWidget(){

}

void DbMySQLWidget::saveData(){
    DatabaseMySQL *db = dynamic_cast<DatabaseMySQL*>(dialog->db.data());
    if(db){
        db->setPort(getPort());
        db->setHostName(getHostName());
        db->setDatabaseName(getDatabaseName());
        db->setUsername(getUsername());
        db->setPassword(getPassword());
    }
}

int DbMySQLWidget::getPort() const{
    return ui->port->value();
}

QString DbMySQLWidget::getHostName() const{
    return ui->hostName->text();
}

QString DbMySQLWidget::getDatabaseName() const{
    return ui->dbName->text();
}

QString DbMySQLWidget::getUsername() const{
    return ui->username->text();
}

QString DbMySQLWidget::getPassword() const{
    return ui->password->text();
}

void DbMySQLWidget::setPort(int p){
    ui->port->setValue(p);
}

void DbMySQLWidget::setHostName(const QString &name){
    ui->hostName->setText(name);
}

void DbMySQLWidget::setDatabaseName(const QString &name){
    ui->dbName->setText(name);
}

void DbMySQLWidget::setUsername(const QString &name){
    ui->username->setText(name);
}

void DbMySQLWidget::setPassword(const QString &pass){
    ui->password->setText(pass);
}
