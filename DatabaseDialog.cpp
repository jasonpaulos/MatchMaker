#include "DatabaseDialog.h"
#include "ui_DatabaseDialog.h"
#include "Environment.h"
#include "DbChooseWidget.h"
#include "DbMySQLWidget.h"
#include "DbSQLiteWidget.h"
#include "DbValidateWidget.h"
#include "DbFieldWidget.h"
#include "DatabaseMySQL.h"
#include "DatabaseSQLite.h"

DatabaseDialog::DatabaseDialog(bool *success, DatabaseSetup *dbSetup, QScopedPointer<Database> &db, QWidget *parent):
    QDialog(parent),
    success(success),
    dbSetup(dbSetup),
    db(db),
    currentState(STATE_NONE),
    currentWidget(NULL),
    ui(new Ui::DatabaseDialog())
{
    ui->setupUi(this);

    *success = false;

    widgetGeometry = ui->activeWidget->geometry();
    widgetName = ui->activeWidget->accessibleName();

    setState(STATE_CHOOSE);
}

DatabaseDialog::~DatabaseDialog(){
    delete ui;
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
    QPushButton *pb = NULL;

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
    QPushButton *pb = NULL, *notDefault[2];

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

    QDialog::closeEvent(event);
}

void DatabaseDialog::on_cancelButton_clicked(){
    *success = false;
    close();
}

void DatabaseDialog::on_backButton_clicked(){
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

void DatabaseDialog::on_nextButton_clicked(){
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

void DatabaseDialog::on_finishButton_clicked(){
    if(currentState == STATE_FIELD){
        if(currentWidget->canFinish()){
            *success = true;
            close();
        }
    }
}
