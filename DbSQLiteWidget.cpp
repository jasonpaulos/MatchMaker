#include "DbSQLiteWidget.h"
#include "ui_DbSQLiteWidget.h"
#include "DatabaseDialog.h"
#include "DatabaseSQLite.h"
#include <QFileDialog>

DbSQLiteWidget::DbSQLiteWidget(DatabaseDialog *parent):
    StepWidget(parent),
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
    delete ui;
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
    QString filePath = QFileDialog::getOpenFileName(
                this,
                tr("Select a Database File"),
                QDir::homePath(),
                tr("SQLite (*.db *.db3 *.sqlite *.sqlite3);; All Files (*)")
    );

    if(!filePath.isNull()){
        ui->path->setText(filePath);
    }
}
