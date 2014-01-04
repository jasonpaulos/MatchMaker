#ifndef PRINTENGINE_H
#define PRINTENGINE_H

#include <QObject>

class PrintEngine : public QObject
{
    Q_OBJECT
public:
    explicit PrintEngine(QObject *parent = 0);

signals:

public slots:

};

#endif // PRINTENGINE_H
