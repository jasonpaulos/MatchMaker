#include "DbMySQLWidget.h"
#include "ui_DbMySQLWidget.h"
#include "DatabaseDialog.h"
#include "DatabaseMySQL.h"

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
    delete ui;
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
