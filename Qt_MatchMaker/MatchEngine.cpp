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

#include "MatchEngine.h"

MatchEngine::MatchEngine(std::vector<User> *input, const std::vector<User> *choices, int matchAmount):
    timer(nullptr),
    input(*input),
    rawChoices(*choices),
    index(0),
    matchesPerSecond(50), //Might want to modify this based on rawChoices.size()
    matchAmount(matchAmount)
{
    connect(this, SIGNAL(pleaseSetup()), this, SLOT(setup()));
    connect(this, SIGNAL(pleaseStartMatching()), this, SLOT(startMatching()));
    connect(this, SIGNAL(pleaseStopMatching()), this, SLOT(stopMatching()));
}


void MatchEngine::setup(){
    timer.reset(new QTimer(this));
    connect(timer.data(), SIGNAL(timeout()), this, SLOT(match()));
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
