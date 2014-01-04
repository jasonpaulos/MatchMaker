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
    delete ui;
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
