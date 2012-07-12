


#include "GridButton.h"


GridButton::GridButton()
{
    
    pos.set(0, 0);
    alpha = minAlpha = 128;
    alphaInc = 3;
    clr = ofColor(int(ofRandom(50,255)), int(ofRandom(50,255)), int(ofRandom(50,255)),alpha);
    //clr = ofColor(255,alpha);
    //clr.setSaturation(255.0f);
    width = 100;
    height = 100;
}


GridButton::~GridButton()
{

}

void GridButton::update() {
    
    if(alpha > minAlpha) alpha -= alphaInc;
    clr.a = alpha;
     
}

void GridButton::draw() {
    
    ofFill();
    ofSetColor(clr);
    ofRect(pos.x, pos.y, width, height);
    
    //ofSetLineWidth(2.0f);
    ofNoFill();
    ofSetColor(255, minAlpha);
    ofRect(pos.x, pos.y, width, height);
}

bool GridButton::checkInside(ofPoint hitPoint) {
    
    float nx = pos.x + width; // hack
    float ny = pos.y + height; // hack
    bool isInside = nx >= hitPoint.x && nx <= hitPoint.x + width && ny >= hitPoint.y && ny <= hitPoint.y + height;
    if(isInside) alpha = 255; 
        
    return isInside;
}
/*{
 alpha = 255; 
 //cout << "touched" << endl;
 } else {
 alpha = minAlpha;
 }*/

