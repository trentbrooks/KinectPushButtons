
#pragma once

#include "ofMain.h"

class Timer {
    
    public:
    
        Timer();
        
        void enableAutoUpdate();
        void disableAutoUpdate();
        void update();
    
        ofEvent<int> onTimerComplete;
        
        // counts up
        void startTimer(float secondsLimit);
        void restartTimer();
    
        // counts down
        void startCountdown(float secondsLimit);
        void restartCountdown();
    
        void stop();
    
        int time;// = 0;
        string getDisplayTime();
    
    protected:
    
        void updateTime(ofEventArgs &e);
        int startingTime;
        //string displayTime;// = "";
        
        
        int cmin;// = 0;
        int csec;// = 0;
        float timeLimit; 
        float secondsLimit;
        bool allowCounting;
        bool isCountingDown;
        
    
        string pad(int value);
    
        
};
