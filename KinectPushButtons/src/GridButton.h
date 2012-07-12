

#pragma  once

#include "ofMain.h"


class GridButton 
{

public:
    

    GridButton();
    virtual ~GridButton();
    
    ofColor clr;
    ofPoint pos;
    int width;
    int height;
    int alpha;
    int minAlpha;
    float alphaInc;
    bool touched;
   
    //
    void update();
    void draw();
    
    bool checkInside(ofPoint hitPoint);

    
protected:


};

