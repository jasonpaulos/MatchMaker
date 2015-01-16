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

#include "DatabaseMySQL.h"
#include "DatabaseSQLite.h"
#include "DatabaseDialog.h"
#include "DbChooseWidget.h"
#include "ui_DbChooseWidget.h"

DbChooseWidget::DbChooseWidget(DatabaseDialog *parent):
    StepWidget(parent),
    ui(new Ui::DbChooseWidget())
{
    ui->setupUi(this);
    on_comboBox_currentIndexChanged(ui->comboBox->currentIndex());

    if(dialog->db){
        setDatabase(dialog->db->getType());
    }

    dialog->setButtonState(DatabaseDialog::BUTTON_BACK, false);
    dialog->setButtonState(DatabaseDialog::BUTTON_NEXT, true);
    dialog->setButtonState(DatabaseDialog::BUTTON_FINISH, false);
    dialog->setDefaultButton(DatabaseDialog::BUTTON_NEXT);
}

DbChooseWidget::~DbChooseWidget(){

}

void DbChooseWidget::saveData(){
    if(!dialog->db || dialog->db->getType() != getDatabase()){
        Database *raw = NULL;

        switch(getDatabase()){
        case DB_MYSQL:
            raw = new DatabaseMySQL();
            break;
        case DB_SQLITE:
            raw = new DatabaseSQLite();
        }

        dialog->db.reset(raw);
    }
}

DatabaseType DbChooseWidget::getDatabase() const{
    return (DatabaseType)ui->comboBox->currentIndex();
}

void DbChooseWidget::setDatabase(DatabaseType type){
    ui->comboBox->setCurrentIndex(type);
}

void DbChooseWidget::on_comboBox_currentIndexChanged(int index){
    switch(index){
    case DB_MYSQL:
        ui->description->setText("Access a MySQL database hosted on a remote server");
        break;
    case DB_SQLITE:
        ui->description->setText("Access an SQLite database on this system");
        break;
    default:
        ui->description->setText("Description");
    }
}
