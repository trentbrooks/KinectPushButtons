


#include "DisplayLayer.h"


DisplayLayer::DisplayLayer()
{
    //isHidden = false;
    tweenSpeed = 0.9;
    color = ofColor(255,255,255,255);//(1.0f,1.0f,1.0f,1.0f);//(255,255,255,255);//
    currentColor = ofColor(255,255,255,255);//(1.0f,1.0f,1.0f,1.0f);//255,255,255,255);//(
    previousColor = ofColor(0,0,0,0);//0.0f,0.0f,0.0f,0.0f);//0,0,0,0);//(
    hasImage = false;
}


DisplayLayer::~DisplayLayer()
{

}

void DisplayLayer::loadImage(string filename) {
    
    image = new ofImage();
    image->loadImage(filename);
    if(image->width < 1920) image->resize(1920, 1080);
    hasImage = true;
}

void DisplayLayer::add(DisplayLayer * di) {
    
    items.push_back(di);
}


void DisplayLayer::update() {
    
    float cr = (float)(currentColor.r)/255.0;
    float cg = (float)(currentColor.g)/255.0;
    float cb = (float)(currentColor.b)/255.0;
    float ca = (float)(currentColor.a)/255.0;
    
    
    float r = (float)(color.r)/255.0;
    float g = (float)(color.g)/255.0;
    float b = (float)(color.b)/255.0;
    float a = (float)(color.a)/255.0;
    
    if(color.a == 255) a = 1.0;
    
    float A = tweenSpeed;
    float B = 1.0 - A;
    
    cr = r*B + cr*A;
    cg = g*B + cg*A;
    cb = b*B + cb*A;
    ca = a*B + ca*A;
    
    float ma = ceil(ca*255);
    if(ca < 0.5)ma = floor(ca*255);
    
    currentColor = ofColor(cr*255, cg*255, cb*255, ma);
    
    // update sublayers
    for(int i = 0; i < items.size(); i++) {
        items[i]->update();
    }
}

void DisplayLayer::draw() {
    
    if(currentColor.a == 0 ) return;
    
    if(hasImage) {
        ofSetColor(currentColor);
        image->draw(0,0);
    }
    
    // draw sublayers
    for(int i = 0; i < items.size(); i++) {
        items[i]->draw();
    }
}

void DisplayLayer::hide(bool tween) {
    
    //isHidden = false;
    //setColor(255,255,255,0,tween);
    previousColor = color;
    color.a = 0;
    if(!tween) currentColor.a = 0;
}

void DisplayLayer::show(bool tween) {
    
    //isHidden = true;
    //setColor(255,255,255,255,tween);
    previousColor = color;
    color.a = 255;
    if(!tween)currentColor.a = 255;

}

void DisplayLayer::setColor(ofColor clr, bool tween) {
    previousColor = color;
    color.r = clr.r / 255.0f;
    color.g = clr.g / 255.0f;
    color.b = clr.b / 255.0f;
    color.a = clr.a / 255.0f;
    
    if(!tween) currentColor = color;
}

void DisplayLayer::setColor(int r, int g, int b, int a, bool tween) {
    previousColor = color;
    color.r = r / 255.0f;
    color.g = g / 255.0f;
    color.b = b / 255.0f;
    color.a = a / 255.0f;
    
    if(!tween) currentColor = color;
}