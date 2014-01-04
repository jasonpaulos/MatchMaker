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

#include "MainWindow.h"
#include "PrintEngine.h"

PrintEngine::PrintEngine(MainWindow *parent):
    hasGrade(parent->matchMaker.dbSetup.hasGrade()),
    saveTo(parent->getPdfSavePath()),
    timer(nullptr),
    printer(nullptr),
    painter(nullptr),
    titleFont("sans-serif", 24, 20),
    textFont("sans-serif", 24),
    index(0),
    pagesPerSecond(50)
{
    connect(this, SIGNAL(pleaseSetup()), this, SLOT(setup()));
    connect(this, SIGNAL(pleaseStartPrinting()), this, SLOT(startPrinting()));
    connect(this, SIGNAL(pleaseStopPrinting()), this, SLOT(stopPrinting()));

    users.resize(parent->matchMaker.male.size() + parent->matchMaker.female.size(), nullptr);

    unsigned int i = 0;
    for(auto u = parent->matchMaker.male.cbegin(); u != parent->matchMaker.male.cend(); ++u){
        users[i++] = &(*u);
    }

    for(auto u = parent->matchMaker.female.cbegin(); u != parent->matchMaker.female.cend(); ++u){
        users[i++] = &(*u);
    }
}

QString PrintEngine::getGradeText(Grade grade){
    switch(grade){
    case Grade::FRESHMAN:
        return "Freshman";
    case Grade::SOPHOMORE:
        return "Sophomore";
    case Grade::JUNIOR:
        return "Junior";
    case Grade::SENIOR:
        return "Senior";
    default:
        return "Unknown";
    }
}

void PrintEngine::setup(){
    timer.reset(new QTimer(this));
    connect(timer.data(), SIGNAL(timeout()), this, SLOT(printPage()));

    printer.reset(new QPrinter(QPrinter::HighResolution));
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOutputFileName(saveTo);
    printer->setPageSize(QPrinter::Letter);
    printer->setOrientation(QPrinter::Portrait);

    pageRect = printer->pageRect();

    /* By default, pageRect will only have margins on the top and left, so here we subtract
     * the margins from the width and height so that we'll have margins on all four sides.
     */
    pageRect.setHeight(2 * pageRect.height() - printer->paperRect().height());
    pageRect.setWidth(2 * pageRect.width() - printer->paperRect().width());

    textMargins.setTop(pageRect.height()/100);
    textMargins.setBottom(textMargins.top());
    textMargins.setLeft(textMargins.top());
    textMargins.setRight(textMargins.top());

    headerRect = pageRect;
    headerRect.setHeight(pageRect.height()/10);

    footerRect = headerRect;
    footerRect.setY(pageRect.y() + pageRect.height() - footerRect.height());
    footerRect.setHeight(pageRect.height()/20);

    titleRect = pageRect;
    titleRect.setY(headerRect.y() + headerRect.height());
    titleRect.setHeight(pageRect.height()/20);

    nameHeaderRect = pageRect;
    nameHeaderRect.setY(titleRect.y() + titleRect.height());
    nameHeaderRect.setWidth(pageRect.width() * 7/10);
    nameHeaderRect.setHeight(pageRect.height()/20);

    gradeHeaderRect = nameHeaderRect;
    gradeHeaderRect.setX(nameHeaderRect.x() + nameHeaderRect.width());
    gradeHeaderRect.setWidth(pageRect.width() - nameHeaderRect.width());

    nameRect = nameHeaderRect;
    nameRect.setY(nameHeaderRect.y() + nameHeaderRect.height());
    nameRect.setHeight(pageRect.height() - nameRect.y() + pageRect.y() - footerRect.height());

    gradeRect = nameRect;
    gradeRect.setX(gradeHeaderRect.x());
    gradeRect.setWidth(gradeHeaderRect.width());

    painter.reset(new QPainter(printer.data()));
    painter->setPen(QPen(QBrush(Qt::black), pageRect.height()/500));

    //Sort users alphabetically
    std::sort(users.begin(), users.end(), [](const User *u1, const User *u2){
        return u1->name < u2->name;
    });
}

void PrintEngine::startPrinting(){
    timer->start(1000/pagesPerSecond);
}

void PrintEngine::stopPrinting(){
    timer->stop();
}

void PrintEngine::printPage(){
    if(index < users.size()){
        const User *user(users[index]);

        if(user){
            const std::vector<const User*> &matches(user->matches);

            painter->setFont(textFont);

            painter->drawText(headerRect.marginsRemoved(textMargins), Qt::AlignVCenter | Qt::AlignLeft, "OC Mingle Matches");
            painter->drawText(headerRect.marginsRemoved(textMargins), Qt::AlignVCenter | Qt::AlignRight, "Feburary, 2014");

            painter->setFont(titleFont);

            painter->drawText(titleRect.marginsRemoved(textMargins), Qt::AlignVCenter | Qt::AlignLeft, "Matches for:");
            painter->drawText(titleRect.marginsRemoved(textMargins), Qt::AlignVCenter | Qt::AlignRight, user->name + (hasGrade ? ", " + getGradeText(user->getGrade()) : ""));

            painter->drawRect(nameHeaderRect);
            painter->drawText(nameHeaderRect.marginsRemoved(textMargins), Qt::AlignBottom | Qt::AlignLeft, "Name");

            painter->drawRect(gradeHeaderRect);
            painter->drawText(gradeHeaderRect.marginsRemoved(textMargins), Qt::AlignBottom | Qt::AlignLeft, "Grade");

            painter->drawRect(nameRect);
            painter->drawRect(gradeRect);

            painter->setFont(textFont);

            QString names, grades;

            unsigned int rank = 0;
            for(auto m = matches.begin(); m != matches.end(); ++m){
                if(const User *match = *m){
                    names += QString::number(++rank) + ".\t" + match->name + "\n";

                    if(hasGrade){
                        grades += getGradeText(match->getGrade()) + "\n";
                    }
                }
            }

            painter->drawText(nameRect.marginsRemoved(textMargins), Qt::AlignTop | Qt::AlignLeft, names);
            painter->drawText(gradeRect.marginsRemoved(textMargins), Qt::AlignTop | Qt::AlignLeft, grades);

            painter->drawRect(footerRect);

            if(index + 1 < users.size()){
                printer->newPage();
            }
        }

        emit progress(++index);
    }else{
        stopPrinting();
        painter->end();
        emit done();
    }
}
