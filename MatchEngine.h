#ifndef MATCHENGINE_H
#define MATCHENGINE_H

#include <map>
#include <QObject>
#include <QTimer>
#include "User.h"

class MatchEngine : public QObject{
    Q_OBJECT

public:
    explicit MatchEngine(std::vector<User> *input, const std::vector<User> *choices, int matchAmount);
    ~MatchEngine();

public slots:
    void setup();
    void startMatching();
    void stopMatching();
    void match();

signals:
    void pleaseStartMatching();
    void pleaseStopMatching();
    void progress(int completed);
    void done();

private:
    QTimer *timer;
    unsigned int index;
    std::vector<User> &input;
    const std::vector<User> &rawChoices;
    std::map<float, const User*> sortedChoices;

public:
    const unsigned int matchesPerSecond, matchAmount;
};

#endif // MATCHENGINE_H
