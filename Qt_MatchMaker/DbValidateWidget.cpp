#include "DatabaseDialog.h"
#include "DbValidateWidget.h"
#include "ui_DbValidateWidget.h"
#include "Environment.h"
#include "MatchMaker.h"
#include "DatabaseMySQL.h"
#include <QMessageBox>
#include <QFileInfo>
#include <QTimer>
#include <QSqlError>
#include <QThread>

DbValidateWidget::DbValidateWidget(DatabaseDialog *parent):
    StepWidget(parent),
    ui(new Ui::DbValidateWidget())
{
    ui->setupUi(this);

    connect(this, SIGNAL(signalShowError(QString)), this, SLOT(slotShowError(QString)));
    connect(this, SIGNAL(signalFillTables(QStringList)), this, SLOT(slotFillTables(QStringList)));

    dialog->setButtonState(DatabaseDialog::BUTTON_BACK, false);
    dialog->setButtonState(DatabaseDialog::BUTTON_NEXT, false);
    dialog->setButtonState(DatabaseDialog::BUTTON_FINISH, false);

    DatabaseManager *dm = MatchMaker::instance->dbManager.data();

    dm->removeConnection(CONNECTION);
    dm->addConnection(CONNECTION, dialog->db.data(),
    [this, dm](QString error){
        if(error.isEmpty()){
            dm->getTables(CONNECTION,
            [this](QStringList tables){
                emit signalFillTables(tables);
            },
            [this](QString error){
                emit signalShowError(error);
            });
        }else{
            emit signalShowError(error);
        }
    });
}

DbValidateWidget::~DbValidateWidget(){
    delete ui;
}

void DbValidateWidget::saveData(){
    QString table(ui->tableBox->currentText());

    if(dialog->dbSetup->getTable() != table){
        *(dialog->dbSetup) = DatabaseSetup(table);
    }
}

void DbValidateWidget::finishedQuery(bool success){
    dialog->setButtonState(DatabaseDialog::BUTTON_BACK, true);

    if(success){
        ui->validLabel->setText("Done");
        ui->validBar->setMaximum(1);
        ui->validBar->setValue(1);

        ui->tableGroup->setEnabled(true);

        dialog->setButtonState(DatabaseDialog::BUTTON_NEXT, true);
        dialog->setDefaultButton(DatabaseDialog::BUTTON_NEXT);
    }else{
        ui->validLabel->setText("Failed");
        ui->validBar->setMaximum(1);
        ui->validBar->setValue(0);
    }
}

void DbValidateWidget::slotShowError(QString error){
    finishedQuery(false);

    QMessageBox::warning(
                this,
                tr("Failed to Open Database"),
                tr("An error occured when trying to open the database:\n\n") + error,
                QMessageBox::Ok
    );
}

void DbValidateWidget::slotFillTables(QStringList tables){
    if(tables.size() > 0){
        finishedQuery(true);

        ui->tableBox->addItems(tables);
    }else{
        slotShowError("There are no tables in this database");
    }
}
