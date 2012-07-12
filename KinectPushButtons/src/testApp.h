#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofxOpenNICapture.h"
#include "ofMain.h"
#include "ofxOpenNIUser.h"
#include "ofxOpenNITracker.h"
#include "ofxXmlSettings.h"
#include "ofxTouchGUI.h"
#include "GridButton.h"


struct Player {
    
    ofPoint leftHand;
    ofPoint rightHand;
    ofPoint hips;
    ofPoint neck;
    ofPoint leftShoulder;
    ofPoint rightShoulder;
    ofPoint leftElbow;
    ofPoint rightElbow;
    
    float lowerLeftArmDistanceZ;// = 0;
    float lowerRightArmDistanceZ;// = 0;    
    float upperLeftArmDistanceZ;// = 0;
    float upperRightArmDistanceZ;// = 0;
    //float leftArmLength = 0;
    //float rightArmLength = 0;
    
    bool leftPressed;
    bool rightPressed;
    bool isLeftAlreadyPressed;
    bool isRightAlreadyPressed;
    //ofPoint center;
};


class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
    void exit();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
    
    bool hasMouseCursor;
	
    // openni
	ofxOpenNI openNI;
	ofxOpenNICapture recorder;
    ofxOpenNITracker playUser;
    float filterFactor;	
	bool bRecording;
    bool usersDetected;
    void updateKinect();
    bool live;
    bool drawMask;
    
    // player
    ofxOpenNIUser * tracked;
    Player player;
    float armDepthRangeZ;// = 300;
    float combinedPressThreshold; // shoulder to elbow & elbow to hand
    float upperPressThreshold; // just shoulder to elbow
    bool allowMultiplePresses;
    int currentUserID;
    //int btnBlocker;
    //int btnBlockerThreshold;
    bool firstSkeletonDeteted;
    int skeletonCalibrationTime;
    int maxSkeletonAlpha;
    int lightSkeletonAlpha;
    
    // debug
    void drawDebug();
    bool debug;
    
    
    //draw grid buttons
    void setupGrid();
    void drawGrid();
    void updateGrid();
    int btnWidth;
    int btnHeight;
    float gridOffsetX;
    float gridOffsetY;
    float gridScale;
    float gridHeightRatio;
    float gridScaleFriction;
    vector<GridButton *> btns;
    GridButton * btn0;
    GridButton * btn1;
    GridButton * btn2;
    GridButton * btn3;
    GridButton * btn4;
    GridButton * btn5;
    GridButton * btn6;
    GridButton * btn7;
    GridButton * btn8;
    ofPoint normalisedLeft;
    ofPoint normalisedRight;
    ofPoint getNormalisedPosInside(ofPoint hitPoint, float x, float y, float w, float h);

    ofFbo fbo;
    ofTexture texture;
    float fboScale;
    int stageWidth;
    int stageHeight;
    int maxWidth;
    int maxHeight;
    int fboOffset;
    //ofxCvGrayscaleImage 	grayImage;
    //ofxCvContourFinder 	contourFinder;
    
    
    
    bool toggleFadeOut;
    int fadeOutThreshold;
    int fadeOut;
    
    // gui
    ofxTouchGUI settings;
    void setupGUI();
    void onButtonPressed(const void* sender, string &buttonLabel);
    
    
};

#endif
