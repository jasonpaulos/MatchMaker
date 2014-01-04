#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QSqlError>
#include <qprinter.h> //<QtPrinter> would not work for some reason
#include <QPainter>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DatabaseDialog.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow()),
    isMaleDone(false),
    isFemaleDone(false),
    maleEngine(nullptr),
    femaleEngine(nullptr),
    maleThread(new QThread()),
    femaleThread(new QThread())
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

    delete ui;
}

void MainWindow::printToPdf(){
    ui->stop->setEnabled(false);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(ui->pdfInfo->text());
    printer.setPageSize(QPrinter::Letter);
    printer.setOrientation(QPrinter::Portrait);

    //Create a vector that contains all users
    std::vector<User> users(matchMaker.male);
    users.insert(users.end(), matchMaker.female.begin(), matchMaker.female.end());

    //Sort users alphabetically
    std::sort(users.begin(), users.end(), [](const User &u1, const User &u2){
        return u1.name < u2.name;
    });

    QPainter painter;
    //TODO: painter.setFont();

    painter.begin(&printer);

    for(auto i = users.cbegin(); i != users.cend(); ++i){
        QString text("Matches for: " + i->name + "\n");
        const std::vector<const User*> &matches(i->matches);

        for(auto m = matches.begin(); m != matches.end(); ++m){
            text += (*m ? (*m)->name + "\t" + QString::number(i->answers.getDistance((*m)->answers)) : "NULL") + "\n";
        }

        painter.drawText(printer.pageRect(), Qt::AlignHCenter | Qt::AlignVCenter | Qt::AlignJustify, text);

        ui->printingProgress->setValue(ui->printingProgress->value() + 1);
        ui->printingInfo->setText(QString::number(ui->printingProgress->value()) + "/" + QString::number(ui->printingProgress->maximum()));

        if(i + 1 != users.cend()){
            printer.newPage();
        }
    }

    //Prints the pdf
    painter.end();
}

void MainWindow::maleQuery(QSqlQuery &query){
    if(!query.lastError().isValid()){

        query.setForwardOnly(true);

        int dimensions = matchMaker.dbSetup.getQuestions().size() + matchMaker.dbSetup.hasGrade();
        bool hasFirst = matchMaker.dbSetup.hasFirstName(), hasMiddle = matchMaker.dbSetup.hasMiddleName(), hasLast = matchMaker.dbSetup.hasLastName();

        while(query.next()){
            int i = 0;
            QString first(hasFirst ? query.value(i++).toString() : ""), middle(hasMiddle ? query.value(i++).toString(): ""), last(hasLast ? query.value(i++).toString() : "");

            User user(
                        first + (middle.isEmpty() ? "" : " ") +
                        middle + (last.isEmpty() ? "" : " ") +
                        last,
                        Gender::MALE,
                        dimensions
            );

            for(int a = 0; a < dimensions; ++a){
                user.answers.elements[a] = query.value(i++).toInt();//TODO: check for error?
            }

            matchMaker.male.push_back(user);
        }

    }else{
        emit signalShowError(query.lastError().text());
    }
}

void MainWindow::femaleQuery(QSqlQuery &query){
    if(!query.lastError().isValid()){

        query.setForwardOnly(true);

        int dimensions = matchMaker.dbSetup.getQuestions().size() + matchMaker.dbSetup.hasGrade();
        bool hasFirst = matchMaker.dbSetup.hasFirstName(), hasMiddle = matchMaker.dbSetup.hasMiddleName(), hasLast = matchMaker.dbSetup.hasLastName();

        while(query.next()){
            int i = 0;
            QString first(hasFirst ? query.value(i++).toString() : ""), middle(hasMiddle ? query.value(i++).toString(): ""), last(hasLast ? query.value(i++).toString() : "");

            User user(
                        first + (middle.isEmpty() ? "" : " ") +
                        middle + (last.isEmpty() ? "" : " ") +
                        last,
                        Gender::FEMALE,
                        dimensions
            );

            for(int a = 0; a < dimensions; ++a){
                user.answers.elements[a] = query.value(i++).toInt();//TODO: check for error?
            }

            matchMaker.female.push_back(user);
        }

        emit signalUsersLoaded();
    }else{
        emit signalShowError(query.lastError().text());
    }
}

void MainWindow::on_selectDatabase_clicked(){
    bool success;
    DatabaseSetup dbSetup;
    QScopedPointer<Database> db;

    DatabaseDialog dialog(&success, &dbSetup, db, this);
    dialog.exec();

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

        ui->progressGroup->setEnabled(true);
        ui->start->setEnabled(true);

        matchMaker.dbSetup = dbSetup;
        matchMaker.db.swap(db);
    }
}

void MainWindow::on_start_clicked(){    
    ui->inputGroup->setEnabled(false);
    ui->outputGroup->setEnabled(false);

    ui->start->setEnabled(false);
    ui->stop->setEnabled(false);
    ui->clear->setEnabled(false);

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
    [this](QSqlQuery query){
        maleQuery(query);
    });
    matchMaker.dbManager->queryConnection(CONNECTION, query + matchMaker.dbSetup.getGender() + " = " + QString::number(Gender::FEMALE),
    [this](QSqlQuery query){
        femaleQuery(query);
    });
}

void MainWindow::on_stop_clicked(){
    ui->start->setEnabled(true);
    ui->stop->setEnabled(false);
    ui->clear->setEnabled(true);

    emit maleEngine->pleaseStopMatching();
    emit femaleEngine->pleaseStopMatching();
}

void MainWindow::on_clear_clicked(){
    ui->start->setEnabled(false);
    ui->clear->setEnabled(false);

    ui->progressGroup->setEnabled(false);
    ui->inputGroup->setEnabled(true);
    ui->outputGroup->setEnabled(false);

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

    matchMaker.male.clear();
    matchMaker.female.clear();

    delete maleEngine;
    delete femaleEngine;

    maleEngine = nullptr;
    femaleEngine = nullptr;
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

    ui->maleProgress->setMaximum((int)matchMaker.male.size());
    ui->femaleProgress->setMaximum((int)matchMaker.female.size());
    ui->totalProgress->setMaximum(ui->maleProgress->maximum() + ui->femaleProgress->maximum());
    ui->printingProgress->setMaximum(ui->totalProgress->maximum());

    ui->maleInfo->setText("0/" + QString::number(ui->maleProgress->maximum()));
    ui->femaleInfo->setText("0/" + QString::number(ui->femaleProgress->maximum()));
    ui->totalInfo->setText("0/" + QString::number(ui->totalProgress->maximum()));
    ui->printingInfo->setText(ui->totalInfo->text());

    maleEngine = new MatchEngine(&matchMaker.male, &matchMaker.female, 10);
    maleEngine->moveToThread(maleThread);

    femaleEngine = new MatchEngine(&matchMaker.female, &matchMaker.male, 10);
    femaleEngine->moveToThread(femaleThread);

    connect(maleThread, SIGNAL(started()), maleEngine, SLOT(setup()));
    connect(femaleThread, SIGNAL(started()), femaleEngine, SLOT(setup()));

    connect(maleEngine, SIGNAL(progress(int)), this, SLOT(maleProgress(int)));
    connect(maleEngine, SIGNAL(done()), this, SLOT(maleDone()));
    connect(femaleEngine, SIGNAL(progress(int)), this, SLOT(femaleProgress(int)));
    connect(femaleEngine, SIGNAL(done()), this, SLOT(femaleDone()));
}

void MainWindow::maleProgress(int complete){
    ui->maleProgress->setValue(complete);
    ui->maleInfo->setText(QString::number(complete) + "/" + QString::number(ui->maleProgress->maximum()));

    int total = complete + ui->femaleProgress->value();
    ui->totalProgress->setValue(total);
    ui->totalInfo->setText(QString::number(total) + "/" + QString::number(ui->totalProgress->maximum()));
}

void MainWindow::femaleProgress(int complete){
    ui->femaleProgress->setValue(complete);
    ui->femaleInfo->setText(QString::number(complete) + "/" + QString::number(ui->femaleProgress->maximum()));

    int total = complete + ui->maleProgress->value();
    ui->totalProgress->setValue(total);
    ui->totalInfo->setText(QString::number(total) + "/" + QString::number(ui->totalProgress->maximum()));
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

void MainWindow::on_selectPdf_clicked(){
    QString filePath = QFileDialog::getSaveFileName(
                this,
                "Save matches",
                QDir::homePath(),
                tr("PDF (*.pdf);; All Files (*)")
    );

    if(!filePath.isNull()){
        ui->pdfInfo->setText(filePath);
    }
}
