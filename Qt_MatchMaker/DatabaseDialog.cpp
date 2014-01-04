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

#include "Environment.h"
#include "DbChooseWidget.h"
#include "DbMySQLWidget.h"
#include "DbSQLiteWidget.h"
#include "DbValidateWidget.h"
#include "DbFieldWidget.h"
#include "DatabaseMySQL.h"
#include "DatabaseSQLite.h"
#include "DatabaseDialog.h"
#include "ui_DatabaseDialog.h"

DatabaseDialog::DatabaseDialog(QWidget *parent):
    QDialog(parent, Qt::Sheet), //Qt::Sheet will make the dialog appear as a sheet in Mac OSX
    success(false),
    db(nullptr),
    currentState(STATE_NONE),
    currentWidget(nullptr),
    ui(new Ui::DatabaseDialog())
{
    ui->setupUi(this);

    widgetGeometry = ui->activeWidget->geometry();
    widgetName = ui->activeWidget->accessibleName();

    setState(STATE_CHOOSE);
}

DatabaseDialog::~DatabaseDialog(){

}

void DatabaseDialog::setState(State state){
    if(currentState == state){
        return;
    }

    if(currentWidget){
       currentWidget->saveData();
    }

    switch(state){
    case STATE_CHOOSE:
        currentWidget = new DbChooseWidget(this);
        break;
    case STATE_MYSQL:
        currentWidget = new DbMySQLWidget(this);
        break;
    case STATE_SQLITE:
        currentWidget = new DbSQLiteWidget(this);
        break;
    case STATE_VALIDATE:
        currentWidget = new DbValidateWidget(this);
        break;
    case STATE_FIELD:
        currentWidget = new DbFieldWidget(this);
    }

    if(ui->activeWidget != currentWidget){
        delete ui->activeWidget;
        ui->activeWidget = currentWidget;
        currentWidget->setVisible(true);
    }

    currentState = state;
}

bool DatabaseDialog::isButtonEnabled(Button button) const{
    switch(button){
    case BUTTON_BACK:
        return ui->backButton->isEnabled();
    case BUTTON_NEXT:
        return ui->nextButton->isEnabled();
    case BUTTON_FINISH:
        return ui->finishButton->isEnabled();
    default:
        return false;
    }
}

void DatabaseDialog::setButtonState(Button button, bool enabled){
    QPushButton *pb = nullptr;

    switch(button){
    case BUTTON_BACK:
        pb = ui->backButton;
        break;
    case BUTTON_NEXT:
        pb = ui->nextButton;
        break;
    case BUTTON_FINISH:
        pb = ui->finishButton;
    }

    if(pb){
        pb->setEnabled(enabled);
    }
}

void DatabaseDialog::setDefaultButton(Button button){
    QPushButton *pb = nullptr, *notDefault[2];

    switch(button){
    case BUTTON_BACK:
        pb = ui->backButton;
        notDefault[0] = ui->nextButton;
        notDefault[1] = ui->finishButton;
        break;
    case BUTTON_NEXT:
        pb = ui->nextButton;
        notDefault[0] = ui->backButton;
        notDefault[1] = ui->finishButton;
        break;
    case BUTTON_FINISH:
        pb = ui->finishButton;
        notDefault[0] = ui->backButton;
        notDefault[1] = ui->nextButton;
    }

    if(pb){
        pb->setDefault(true);
        notDefault[0]->setDefault(false);
        notDefault[1]->setDefault(false);
    }
}

void DatabaseDialog::closeEvent(QCloseEvent *event){
    if(currentWidget){
       currentWidget->saveData();
    }

    emit finished(success, db, dbSetup);

    QDialog::closeEvent(event);
}

void DatabaseDialog::on_cancelButton_clicked(){
    success = false;
    close();
}

void DatabaseDialog::on_backButton_clicked(){
    if(!currentWidget || currentWidget->canGoBack()){
        if(currentState == STATE_FIELD){
            setState(STATE_VALIDATE);
        }else if(currentState == STATE_VALIDATE){
            switch(db->getType()){
            case DB_MYSQL:
                setState(STATE_MYSQL);
                break;
            case DB_SQLITE:
                setState(STATE_SQLITE);
            }
        }else{
            setState(STATE_CHOOSE);
        }
    }
}

void DatabaseDialog::on_nextButton_clicked(){
    if(!currentWidget || currentWidget->canFinish()){
        if(currentState == STATE_CHOOSE){
            DbChooseWidget *widget = static_cast<DbChooseWidget*>(ui->activeWidget);

            switch(widget->getDatabase()){
            case DB_MYSQL:
                setState(STATE_MYSQL);
                break;
            case DB_SQLITE:
                setState(STATE_SQLITE);
            }
        }else if(currentState == STATE_MYSQL || currentState == STATE_SQLITE){
            setState(STATE_VALIDATE);
        }else if(currentState == STATE_VALIDATE){
            setState(STATE_FIELD);
        }
    }
}

void DatabaseDialog::on_finishButton_clicked(){
    if(currentState == STATE_FIELD && currentWidget->canFinish()){
        success = true;
        close();
    }
}
