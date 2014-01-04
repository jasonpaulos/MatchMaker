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

#include <QMessageBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlError>
#include "DatabaseDialog.h"
#include "Environment.h"
#include "MatchMaker.h"
#include "DbFieldWidget.h"
#include "ui_DbFieldWidget.h"

DbFieldWidget::DbFieldWidget(DatabaseDialog *parent):
    StepWidget(parent),
    ui(new Ui::DbFieldWidget())
{
    ui->setupUi(this);

    connect(this, SIGNAL(signalProcessQuery(QSqlQuery)), this, SLOT(slotProcessQuery(QSqlQuery)));

    dialog->setButtonState(DatabaseDialog::BUTTON_BACK, true);
    dialog->setButtonState(DatabaseDialog::BUTTON_NEXT, false);
    dialog->setButtonState(DatabaseDialog::BUTTON_FINISH, false);

    DatabaseManager *dm = MatchMaker::instance->dbManager;

    dm->queryConnection(CONNECTION, dialog->db->getColumnQuery(dialog->dbSetup.getTable()),
    [this](QSqlQuery query){
        emit signalProcessQuery(query);
    });
}

DbFieldWidget::~DbFieldWidget(){

}

void DbFieldWidget::saveData(){
    dialog->dbSetup.setFirstName(ui->firstBox->currentIndex() == 0 ? "" : ui->firstBox->currentText());
    dialog->dbSetup.setMiddleName(ui->middleBox->currentIndex() == 0 ? "" : ui->middleBox->currentText());
    dialog->dbSetup.setLastName(ui->lastBox->currentIndex() == 0 ? "" : ui->lastBox->currentText());
    dialog->dbSetup.setGrade(ui->gradeBox->currentIndex() == 0 ? "" : ui->gradeBox->currentText());
    dialog->dbSetup.setGender(ui->genderBox->currentText());

    dialog->dbSetup.clearQuestions();

    for(auto i = questionFields.begin(); i != questionFields.end(); ++i){
        QCheckBox *box = *i;

        if(box->isChecked()){
            dialog->dbSetup.addQuestion(box->text());
        }
    }
}

bool DbFieldWidget::canFinish(){

    //Is there a first, middle, or last name? Ifso, is at least one question field selected?
    if(ui->firstBox->currentIndex() > 0 || ui->middleBox->currentIndex() > 0 || ui->lastBox->currentIndex() > 0){
        for(int i = 0; i < questionFields.size(); ++i){
            if(questionFields.at(i)->isChecked()){
                return true;
            }
        }
    }

    QMessageBox::warning(
                this,
                tr("Unselected fields"),
                tr("Please specify a first, middle, or last name field and select at least one question field to finish."),
                QMessageBox::Ok
    );

    return false;
}

void DbFieldWidget::showError(const QString &error){
    QMessageBox::warning(
                this,
                tr("Failed to Find Fields"),
                tr("An error occured when trying to find the fields in the table '") + dialog->dbSetup.getTable() + "':\n\n" + error,
                QMessageBox::Ok
    );
}

void DbFieldWidget::slotProcessQuery(QSqlQuery query){
    if(!query.lastError().isValid()){
        QStringList fields;
        QSqlRecord rec(query.record());

        if(rec.count() > 0){
            for(int i = 0; i < rec.count(); ++i){
                fields << rec.fieldName(i);
            }

            ui->firstBox->addItems(fields);
            ui->middleBox->addItems(fields);
            ui->lastBox->addItems(fields);
            ui->gradeBox->addItems(fields);
            ui->genderBox->addItems(fields);

            QVBoxLayout *layout = new QVBoxLayout();
            QWidget *holder = new QWidget(ui->questionScrollArea);
            holder->setLayout(layout);

            questionFields.resize(fields.size());

            for(int i = 0; i < fields.size(); ++i){
                QCheckBox *box = new QCheckBox(holder);
                box->setText(fields.at(i));
                questionFields[i] = box;

                layout->addWidget(box);
            }

            ui->questionScrollArea->setWidget(holder);

            dialog->setButtonState(DatabaseDialog::BUTTON_FINISH, true);
        }else{
            showError("There are no fields in this table");
        }
    }else{
        showError(query.lastError().text());
    }
}

void DbFieldWidget::on_questionSelect_clicked(){
    for(int i = 0; i < questionFields.size(); ++i){
        questionFields[i]->setChecked(true);
    }
}

void DbFieldWidget::on_questionDeselect_clicked(){
    for(int i = 0; i < questionFields.size(); ++i){
        questionFields[i]->setChecked(false);
    }
}
