#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include "MatchEngine.h"
#include "MatchMaker.h"

namespace Ui{
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void printToPdf();
    void maleQuery(QSqlQuery &query);
    void femaleQuery(QSqlQuery &query);

private slots:
    void on_selectDatabase_clicked();
    void on_start_clicked();
    void on_stop_clicked();
    void on_clear_clicked();
    void on_selectPdf_clicked();

public slots:
    void slotShowError(QString error);
    void slotUsersLoaded();
    void maleProgress(int complete);
    void femaleProgress(int complete);
    void maleDone();
    void femaleDone();

signals:
    void signalShowError(QString error);
    void signalUsersLoaded();

public:
    MatchMaker matchMaker;

private:
    bool isMaleDone, isFemaleDone;
    MatchEngine *maleEngine, *femaleEngine;
    QThread *maleThread, *femaleThread;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
