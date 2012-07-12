
#include "Timer.h"


Timer::Timer() { 
    
    timeLimit = 10000; // 10 seconds
    secondsLimit = 10;
    startingTime = 0;
    //displayTime = "";
    time = 0;
    cmin = 0;
    csec = 0;
    allowCounting = false;
    isCountingDown = false; // counts up or down
}

void Timer::enableAutoUpdate() {
    ofAddListener(ofEvents.update, this, &Timer::updateTime);
}

void Timer::disableAutoUpdate() {
    ofRemoveListener(ofEvents.update, this, &Timer::updateTime);
}

void Timer::updateTime(ofEventArgs &e) {
    
    update();
}

void Timer::update() {
    
    if(allowCounting) {
        
        if(isCountingDown) {
            time = timeLimit - (ofGetElapsedTimeMillis() - startingTime);
            csec = int(time / 1000);
            cmin = int(csec / 60);
            csec = csec % 60;
            
            if(time < 0) {
                
                //cout << "coutdown finished." << endl;
                allowCounting = false;
                ofNotifyEvent(onTimerComplete,time,this);
            }
            
        } else {
            time = ofGetElapsedTimeMillis() - startingTime;
            csec = int(time / 1000);
            cmin = int(csec / 60);
            csec = csec % 60;
            
            if(time >= timeLimit) {
                
                //cout << "timer finished" << endl;
                allowCounting = false;
                ofNotifyEvent(onTimerComplete,time,this);
            }
        }
        
    }
    
}

string Timer::getDisplayTime() {
    
    return pad(cmin) + ":" + pad(csec);
}


void Timer::startTimer(float timeLimitSeconds) {
    
    secondsLimit = timeLimitSeconds;
    timeLimit = secondsLimit * 1000;
    startingTime = ofGetElapsedTimeMillis();
    isCountingDown = false;
    if(!allowCounting) allowCounting = true;
}


void Timer::startCountdown(float timeLimitSeconds) {
    
    startTimer(timeLimitSeconds);
    isCountingDown = true;
}

void Timer::stop() {
    
    allowCounting = false;
}

void Timer::restartTimer() {
    
    startTimer(secondsLimit);
    //cout << timeLimit << endl;
}

void Timer::restartCountdown() {
    
    startCountdown(secondsLimit);
    //cout << timeLimit << endl;
}

// adds a leading zero
string Timer::pad(int value)
{
    if(value < 10) return "0" + ofToString(value);
    
    return ofToString(value);
}

