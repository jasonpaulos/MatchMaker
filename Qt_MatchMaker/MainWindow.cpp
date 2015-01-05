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
#include <QFileDialog>
#include <QFileInfo>
#include <QSqlError>
#include <QPainter>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DatabaseDialog.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow()),
    partialStop(false),
    isMaleDone(false),
    isFemaleDone(false),
    maleEngine(nullptr),
    femaleEngine(nullptr),
    printEngine(nullptr),
    maleThread(new QThread()),
    femaleThread(new QThread()),
    dialog(nullptr),
    pdfDialog(nullptr)
{
    ui->setupUi(this);
    ui->pdfInfo->setText(QDir::homePath() + "/matches.pdf");

    connect(this, SIGNAL(signalShowError(QString)), this, SLOT(slotShowError(QString)));
    connect(this, SIGNAL(signalUsersLoaded()), this, SLOT(slotUsersLoaded()));

    MatchMaker::instance = &matchMaker;

    maleThread->start();
    femaleThread->start();
}

MainWindow::~MainWindow(){
    maleThread->quit();
    femaleThread->quit();

    maleThread->deleteLater();
    femaleThread->deleteLater();

    if(maleEngine){
        maleEngine->deleteLater();
    }

    if(femaleEngine){
        femaleEngine->deleteLater();
    }

    if(printEngine){
        printEngine->deleteLater();
    }

    delete dialog;
    delete pdfDialog;
}

QString MainWindow::getPdfSavePath(){
    return ui->pdfInfo->text();
}

QString MainWindow::getPdfPageTitle(){
    return ui->titleEdit->text();
}

void MainWindow::printToPdf(){
    printEngine = new PrintEngine(this);

    //We'll reuse femaleThead to host printEngine
    printEngine->moveToThread(femaleThread);

    connect(printEngine, SIGNAL(progress(int)), this, SLOT(printingProgress(int)));
    connect(printEngine, SIGNAL(done()), this, SLOT(printingDone()));

    emit printEngine->pleaseSetup();
    emit printEngine->pleaseStartPrinting();
}

void MainWindow::userQuery(QSqlQuery *query, Gender gen, std::vector<User> &users){
    if(query->exec()){
        unsigned int dimensions = matchMaker.dbSetup.getQuestions().size() + matchMaker.dbSetup.hasGrade();
        bool hasFirst = matchMaker.dbSetup.hasFirstName(), hasMiddle = matchMaker.dbSetup.hasMiddleName(), hasLast = matchMaker.dbSetup.hasLastName();

        while(query->next()){
            int i = 0;
            QString first(hasFirst ? query->value(i++).toString() : ""), middle(hasMiddle ? query->value(i++).toString(): ""), last(hasLast ? query->value(i++).toString() : "");

            User user(
                        first + (middle.isEmpty() ? "" : " ") +
                        middle + (last.isEmpty() ? "" : " ") +
                        last,
                        gen,
                        dimensions
            );

            for(unsigned int a = 0; a < dimensions; ++a){
                user.answers.elements[a] = query->value(i++).toInt();//TODO: check for error?
            }

            users.push_back(user);
        }

    }else{
        emit signalShowError(query->lastError().text());
    }
}

void MainWindow::on_selectDatabase_clicked(){
    if(!dialog && !pdfDialog){
        dialog = new DatabaseDialog(this);

        connect(dialog, SIGNAL(finished(bool, QScopedPointer<Database>&, DatabaseSetup&)), this, SLOT(databaseDialogFinished(bool, QScopedPointer<Database>&, DatabaseSetup&)));

        dialog->show();
    }
}

void MainWindow::on_start_clicked(){
    ui->start->setEnabled(false);
    ui->stop->setEnabled(false);
    ui->clear->setEnabled(false);

    //TODO: check that the pdf file is a valid file name

    if(partialStop){
        if(!isMaleDone){
            emit maleEngine->pleaseStartMatching();
        }

        if(!isFemaleDone){
            emit femaleEngine->pleaseStartMatching();
        }

        if(isMaleDone && isFemaleDone){
            emit printEngine->pleaseStartPrinting();
        }
    }else{
        isMaleDone = isFemaleDone = false;

        ui->inputGroup->setEnabled(false);
        ui->outputGroup->setEnabled(false);

        ui->usersProgress->setMaximum(0);
        ui->usersProgress->setValue(-1);
        ui->usersInfo->setText("Loading...");

        QString query("SELECT " +
                      (matchMaker.dbSetup.hasFirstName() ? matchMaker.dbSetup.getFirstName() + ", " : "") +
                      (matchMaker.dbSetup.hasMiddleName() ? matchMaker.dbSetup.getMiddleName() + ", " : "") +
                      (matchMaker.dbSetup.hasLastName() ? matchMaker.dbSetup.getLastName() + ", " : "") +
                      (matchMaker.dbSetup.hasGrade() ? matchMaker.dbSetup.getGrade() + ", " : "")
        );

        const QStringList &questions(matchMaker.dbSetup.getQuestions());

        for(auto i = questions.begin(); i != questions.end(); ++i){
            query += *i + (questions.endsWith(*i) ? " ": ", ");
        }

        query += "FROM " + matchMaker.dbSetup.getTable() + " WHERE ";

        matchMaker.dbManager->queryConnection(CONNECTION, query + matchMaker.dbSetup.getGender() + " = " + QString::number(Gender::MALE),
        [this, query](QSqlQuery *maleQuery){
            userQuery(maleQuery, Gender::MALE, matchMaker.male);

            matchMaker.dbManager->queryConnection(CONNECTION, query + matchMaker.dbSetup.getGender() + " = " + QString::number(Gender::FEMALE),
            [this](QSqlQuery *femaleQuery){
                userQuery(femaleQuery, Gender::FEMALE, matchMaker.female);

                emit signalUsersLoaded();
            });
        });
    }
}

void MainWindow::on_stop_clicked(){
    partialStop = true;

    ui->start->setEnabled(true);
    ui->stop->setEnabled(false);
    ui->clear->setEnabled(true);

    if(!isMaleDone){
        emit maleEngine->pleaseStopMatching();
    }

    if(!isFemaleDone){
        emit femaleEngine->pleaseStopMatching();
    }

    if(isMaleDone && isFemaleDone){
        emit printEngine->pleaseStartPrinting();
    }
}

void MainWindow::on_clear_clicked(){
    partialStop = false;

    ui->start->setEnabled(true);
    ui->clear->setEnabled(false);

    ui->inputGroup->setEnabled(true);
    ui->outputGroup->setEnabled(true);

    ui->usersProgress->setMaximum(1);
    ui->usersProgress->setValue(0);
    ui->usersInfo->setText("");

    ui->maleProgress->setMaximum(1);
    ui->maleProgress->setValue(0);
    ui->maleInfo->setText("0/0");

    ui->femaleProgress->setMaximum(1);
    ui->femaleProgress->setValue(0);
    ui->femaleInfo->setText("0/0");

    ui->totalProgress->setMaximum(1);
    ui->totalProgress->setValue(0);
    ui->totalInfo->setText("0/0");

    ui->printingProgress->setMaximum(1);
    ui->printingProgress->setValue(0);
    ui->printingInfo->setText("0/0");

    matchMaker.male.clear();
    matchMaker.female.clear();

    if(maleEngine){
        maleEngine->deleteLater();
        maleEngine = nullptr;
    }

    if(femaleEngine){
        femaleEngine->deleteLater();
        femaleEngine = nullptr;
    }

    if(printEngine){
        printEngine->deleteLater();
        printEngine = nullptr;
    }
}

void MainWindow::on_selectPdf_clicked(){
    if(!pdfDialog && !dialog){

        //Qt::Sheet will make the dialog appear as a sheet in Mac OSX
        pdfDialog = new QFileDialog(this, Qt::Sheet);

        pdfDialog->setAcceptMode(QFileDialog::AcceptSave);
        //pdfDialog->setWindowModality(Qt::WindowModal);

        pdfDialog->setWindowTitle(tr("Save matches"));
        pdfDialog->setDirectory(QDir::homePath());
        pdfDialog->setNameFilter(tr("PDF (*.pdf);; All Files (*)"));

        pdfDialog->open(this, SLOT(pdfFileSelected(QString)));
        connect(pdfDialog, SIGNAL(rejected()), this, SLOT(pdfFileCancelled()));

        pdfDialog->show();
    }
}

void MainWindow::databaseDialogFinished(bool success, QScopedPointer<Database> &db, DatabaseSetup &dbSetup){
    if(success){
        QString info;

        switch(db->getType()){
        case DB_MYSQL:
            info = "MySQL: ";
            break;
        case DB_SQLITE:
            info = "SQLite: ";
            break;
        default:
            info = "Database type was not recognized";
        }

        info += db->getDatabaseName();

        ui->databaseInfo->setText(info);

        int questions = dbSetup.getQuestions().size();

        ui->databaseQuestions->setText(questions == 1 ? "1 question" : QString::number(questions) + " questions");

        ui->start->setEnabled(true);

        matchMaker.dbSetup = dbSetup;
        matchMaker.db.swap(db);
    }

    disconnect(dialog, SIGNAL(finished(bool, QScopedPointer<Database>&, DatabaseSetup&)), this, SLOT(databaseDialogFinished(bool, QScopedPointer<Database>&, DatabaseSetup&)));

    dialog = nullptr;
}

void MainWindow::pdfFileSelected(const QString &file){
    if(!file.isNull()){
        ui->pdfInfo->setText(file);
    }

    disconnect(pdfDialog, SIGNAL(rejected()), this, SLOT(pdfFileCancelled()));

    pdfDialog = nullptr;
}

void MainWindow::pdfFileCancelled(){
    disconnect(pdfDialog, SIGNAL(rejected()), this, SLOT(pdfFileCancelled()));

    pdfDialog = nullptr;
}

void MainWindow::slotShowError(QString error){
    ui->usersProgress->setMaximum(1);
    ui->usersProgress->setValue(0);
    ui->usersInfo->setText("Failed");

    QMessageBox::warning(
                this,
                tr("Failed to Load Users"),
                tr("An error occured when trying to load users from the database:\n\n") + error,
                QMessageBox::Ok
    );
}

void MainWindow::slotUsersLoaded(){
    ui->stop->setEnabled(true);

    ui->usersProgress->setMaximum(1);
    ui->usersProgress->setValue(1);
    ui->usersInfo->setText("Done");

    ui->maleProgress->setMaximum(static_cast<int>(matchMaker.male.size()));
    ui->femaleProgress->setMaximum(static_cast<int>(matchMaker.female.size()));
    ui->totalProgress->setMaximum(ui->maleProgress->maximum() + ui->femaleProgress->maximum());
    ui->printingProgress->setMaximum(ui->totalProgress->maximum());

    ui->maleInfo->setText("0/" + QString::number(ui->maleProgress->maximum()));
    ui->femaleInfo->setText("0/" + QString::number(ui->femaleProgress->maximum()));
    ui->totalInfo->setText("0/" + QString::number(ui->totalProgress->maximum()));
    ui->printingInfo->setText(ui->totalInfo->text());

    MathVec max(std::vector<float>(matchMaker.dbSetup.getQuestions().size() + 1, static_cast<float>(ui->rangeSpinBox->value())));
    max.elements.back() = 3.0F; //3 because one "question" is grade level
    float mag = max.getMagnitude();

    maleEngine = new MatchEngine(&matchMaker.male, &matchMaker.female, ui->matchAmountSpinner->value(), mag);
    maleEngine->moveToThread(maleThread);

    femaleEngine = new MatchEngine(&matchMaker.female, &matchMaker.male, ui->matchAmountSpinner->value(), mag);
    femaleEngine->moveToThread(femaleThread);

    connect(maleEngine, SIGNAL(progress(int)), this, SLOT(maleProgress(int)));
    connect(maleEngine, SIGNAL(done()), this, SLOT(maleDone()));
    connect(femaleEngine, SIGNAL(progress(int)), this, SLOT(femaleProgress(int)));
    connect(femaleEngine, SIGNAL(done()), this, SLOT(femaleDone()));

    emit maleEngine->pleaseSetup();
    emit femaleEngine->pleaseSetup();

    emit maleEngine->pleaseStartMatching();
    emit femaleEngine->pleaseStartMatching();
}

void MainWindow::maleProgress(int complete){
    ui->maleProgress->setValue(complete);
    ui->maleInfo->setText(QString::number(complete) + "/" + QString::number(ui->maleProgress->maximum()));

    complete += ui->femaleProgress->value();
    ui->totalProgress->setValue(complete);
    ui->totalInfo->setText(QString::number(complete) + "/" + QString::number(ui->totalProgress->maximum()));
}

void MainWindow::femaleProgress(int complete){
    ui->femaleProgress->setValue(complete);
    ui->femaleInfo->setText(QString::number(complete) + "/" + QString::number(ui->femaleProgress->maximum()));

    complete += ui->maleProgress->value();
    ui->totalProgress->setValue(complete);
    ui->totalInfo->setText(QString::number(complete) + "/" + QString::number(ui->totalProgress->maximum()));
}

void MainWindow::printingProgress(int complete){
    ui->printingProgress->setValue(complete);
    ui->printingInfo->setText(QString::number(complete) + "/" + QString::number(ui->printingProgress->maximum()));
}

void MainWindow::maleDone(){
    isMaleDone = true;

    if(isFemaleDone){
        printToPdf();
    }
}

void MainWindow::femaleDone(){
    isFemaleDone = true;

    if(isMaleDone){
        printToPdf();
    }
}

void MainWindow::printingDone(){
    ui->stop->setEnabled(false);
    ui->clear->setEnabled(true);
}
