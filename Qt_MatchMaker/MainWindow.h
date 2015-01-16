/* Copyright (c) 2015 Jason Paulos
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QScopedPointer>
#include <QMainWindow>
#include <QFileDialog>
#include <QSqlQuery>
#include "MatchEngine.h"
#include "PrintEngine.h"
#include "MatchMaker.h"

namespace Ui{
    class MainWindow;
}

class DatabaseDialog;

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString getPdfSavePath();
    QString getPdfPageTitle();
    QFont getPdfTitleFont();
    QFont getPdfTextFont();
    void printToPdf();
    void userQuery(QSqlQuery *query, Gender gen, std::vector<User> &users);

private slots:
    void on_selectDatabase_clicked();
    void on_start_clicked();
    void on_stop_clicked();
    void on_clear_clicked();
    void on_selectPdf_clicked();
    void on_titleFontComboBox_currentFontChanged(QFont font);
    void on_titleFontStyleBold_toggled(bool checked);
    void on_titleFontStyleItalic_toggled(bool checked);
    void on_titleFontStyleUnderscore_toggled(bool checked);

public slots:
    void databaseDialogFinished(bool success, QScopedPointer<Database> &db, DatabaseSetup &dbSetup);
    void pdfFileSelected(const QString &file);
    void pdfFileCancelled();
    void slotShowError(QString error);
    void slotUsersLoaded();
    void maleProgress(int complete);
    void femaleProgress(int complete);
    void printingProgress(int complete);
    void maleDone();
    void femaleDone();
    void printingDone();

signals:
    void signalShowError(QString error);
    void signalUsersLoaded();

public:
    MatchMaker matchMaker;

private:
    bool partialStop, isMaleDone, isFemaleDone;
    MatchEngine *maleEngine, *femaleEngine;
    PrintEngine *printEngine;
    QThread *maleThread, *femaleThread;
    DatabaseDialog *dialog;
    QFileDialog *pdfDialog;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
