#include <map>
#include "MatchEngine.h"

MatchEngine::MatchEngine(std::vector<User> *input, const std::vector<User> *choices, int matchAmount):
    timer(nullptr),
    input(*input),
    rawChoices(*choices),
    index(0),
    matchesPerSecond(50),
    matchAmount(matchAmount)
{
    connect(this, SIGNAL(pleaseStartMatching()), this, SLOT(startMatching()));
    connect(this, SIGNAL(pleaseStopMatching()), this, SLOT(stopMatching()));
}

MatchEngine::~MatchEngine(){
    delete timer;
}

void MatchEngine::setup(){
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(match()));

    startMatching();
}

void MatchEngine::startMatching(){
    timer->start(1000/matchesPerSecond);
}

void MatchEngine::stopMatching(){
    timer->stop();
}

void MatchEngine::match(){
    if(index < input.size()){
        User &user(input[index]);

        sortedChoices.clear();

        for(auto c = rawChoices.begin(); c != rawChoices.end(); ++c){
            sortedChoices[user.answers.getDistanceSquared(c->answers)] = &(*c);
        }

        user.matches.resize(matchAmount, nullptr);
        unsigned int m = 0;
        for(auto match = sortedChoices.cbegin(); m < matchAmount && match != sortedChoices.cend(); ++match){
            user.matches[m++] = match->second;
        }

        emit progress(++index);
    }else{
        stopMatching();
        emit done();
    }
}
