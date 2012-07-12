

#pragma  once

#include "ofMain.h"


class DisplayLayer 
{

public:
    
    DisplayLayer();
    virtual ~DisplayLayer();
    
    void add(DisplayLayer * di);
    vector<DisplayLayer *> items;
    
    float tweenSpeed;
    //void setColor(ofColor clr, bool tween);
    void setColor(ofColor clr, bool tween);
    void setColor(int r, int g, int b, int a, bool tween);
    ofColor color;
    ofColor currentColor;
    ofColor previousColor;
    
    void loadImage(string filename);
    ofImage * image;
    bool hasImage;

    void hide(bool tween = true);
    bool isHidden;
    void show(bool tween = true);
   
    //
    void update();
    void draw();
    

    
protected:


};

