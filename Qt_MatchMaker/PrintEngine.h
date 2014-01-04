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

#ifndef PRINTENGINE_H
#define PRINTENGINE_H

#include <QScopedPointer>
#include <QObject>
#include <QTimer>
#include <QPainter>
#include <QFont>
#include <QRect>
#include <QMargins>
#include <qprinter.h> //<QtPrinter> would not work for some reason
#include "User.h"

class MainWindow;

class PrintEngine : public QObject{
    Q_OBJECT

public:
    explicit PrintEngine(MainWindow *parent);

    /* Might want to make this constexpr
     */
    QString getGradeText(Grade grade);

public slots:
    void setup();
    void startPrinting();
    void stopPrinting();
    void printPage();

signals:
    void pleaseSetup();
    void pleaseStartPrinting();
    void pleaseStopPrinting();
    void progress(int complete);
    void done();

private:
    bool hasGrade;
    QString saveTo;
    QScopedPointer<QTimer> timer;
    QScopedPointer<QPrinter> printer;
    QScopedPointer<QPainter> painter;
    QFont titleFont, textFont;
    QRect pageRect, headerRect, titleRect, nameRect, nameHeaderRect, gradeRect, gradeHeaderRect, footerRect;
    QMargins textMargins;
    unsigned int index;
    std::vector<const User*> users;

public:
    const unsigned int pagesPerSecond;
};

#endif // PRINTENGINE_H
