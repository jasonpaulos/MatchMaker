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
#include "DatabaseSQLite.h"
#include "DbSQLiteWidget.h"
#include "ui_DbSQLiteWidget.h"

DbSQLiteWidget::DbSQLiteWidget(DatabaseDialog *parent):
    StepWidget(parent),
    fileDialog(nullptr),
    ui(new Ui::DbSQLiteWidget())
{
    ui->setupUi(this);

    DatabaseSQLite *db = dynamic_cast<DatabaseSQLite*>(dialog->db.data());
    if(db){
        setDatabaseName(db->getDatabaseName());
    }

    dialog->setButtonState(DatabaseDialog::BUTTON_BACK, true);
    dialog->setButtonState(DatabaseDialog::BUTTON_NEXT, true);
    dialog->setButtonState(DatabaseDialog::BUTTON_FINISH, false);
    dialog->setDefaultButton(DatabaseDialog::BUTTON_NEXT);
}

DbSQLiteWidget::~DbSQLiteWidget(){
    delete fileDialog;
}

void DbSQLiteWidget::saveData(){
    DatabaseSQLite *db = dynamic_cast<DatabaseSQLite*>(dialog->db.data());
    if(db){
        db->setDatabaseName(getDatabaseName());
    }
}

QString DbSQLiteWidget::getDatabaseName() const{
    return ui->path->text();
}

void DbSQLiteWidget::setDatabaseName(const QString &name){
    ui->path->setText(name);
}

void DbSQLiteWidget::on_browseButton_clicked(){
    if(!fileDialog){
        dialog->setButtonState(DatabaseDialog::BUTTON_BACK, false);
        dialog->setButtonState(DatabaseDialog::BUTTON_NEXT, false);

        //Qt::Sheet will make the dialog appear as a sheet in Mac OSX
        fileDialog = new QFileDialog(this, Qt::Sheet);

        fileDialog->setFileMode(QFileDialog::ExistingFile);
        fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
        //fileDialog->setWindowModality(Qt::WindowModal);

        fileDialog->setWindowTitle(tr("Select a Database File"));
        fileDialog->setDirectory(QDir::homePath());
        fileDialog->setNameFilter(tr("SQLite (*.db *.db3 *.sqlite *.sqlite3);; All Files (*)"));

        fileDialog->open(this, SLOT(fileDialogSelected(QString)));
        connect(fileDialog, SIGNAL(rejected()), this, SLOT(fileDialogCancelled()));

        fileDialog->show();
    }
}

void DbSQLiteWidget::fileDialogSelected(const QString &file){
    if(!file.isNull()){
        ui->path->setText(file);
    }

    disconnect(fileDialog, SIGNAL(rejected()), this, SLOT(fileDialogCancelled()));
    fileDialog = nullptr;

    dialog->setButtonState(DatabaseDialog::BUTTON_BACK, true);
    dialog->setButtonState(DatabaseDialog::BUTTON_NEXT, true);
}

void DbSQLiteWidget::fileDialogCancelled(){
    disconnect(fileDialog, SIGNAL(rejected()), this, SLOT(fileDialogCancelled()));
    fileDialog = nullptr;

    dialog->setButtonState(DatabaseDialog::BUTTON_BACK, true);
    dialog->setButtonState(DatabaseDialog::BUTTON_NEXT, true);
}
