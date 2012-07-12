#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(60);

    // gui props
    live = false;
    debug = true;
    armDepthRangeZ = 300; // arbitrary z depth difference
    combinedPressThreshold = 1.0f; // 0 -2
    upperPressThreshold = 0.5f;
    allowMultiplePresses = false;
    gridScale = 1.0f;
    gridHeightRatio = 0.75f;
    gridScaleFriction = 0.03f;
    firstSkeletonDeteted = false;
    skeletonCalibrationTime = 12;
    maxSkeletonAlpha = 255;
    lightSkeletonAlpha = 150;
        
    setupGrid();
    
    setupGUI();
    
    // openni
    //live = true;
    if(live){
		openNI.setupFromXML("openni/config/ofxopenni_config.xml",false);
	}else{
		openNI.setupFromRecording("recording.oni");
	}
    
    //openNI.setDepthColoring(ofxOpenNI::COLORING_GREY);
    //openNI.setDepthColoring(ofxOpenNI::COLORING_BLUES);
    //openNI.setDepthColoring(ofxOpenNI::COLORING_RAINBOW);
    //openNI.setDepthColoring(ofxOpenNI::COLORING_PSYCHEDELIC);
    //filterFactor = .7f;//7;//0.99;//1.0f;//0.9f; //0.1 = quick/jumpy, 0.9 = slow/smooth
    //playUser.setSmoothing(filterFactor);
	bRecording = false;
    
    playUser.setup(openNI);
    
    stageWidth = ofGetWidth(); // kinect scaled width + height
    stageHeight = ofGetHeight();

}



void testApp::setupGrid() {
    
    // manually set colours of buttons
    btn0 = new GridButton(); btns.push_back(btn0); 
    btn1 = new GridButton(); btns.push_back(btn1); 
    btn2 = new GridButton(); btns.push_back(btn2);
    btn3 = new GridButton(); btns.push_back(btn3); 
    btn4 = new GridButton(); btns.push_back(btn4); 
    btn5 = new GridButton(); btns.push_back(btn5); 
    btn6 = new GridButton(); btns.push_back(btn6); 
    btn7 = new GridButton(); btns.push_back(btn7); 
    btn8 = new GridButton(); btns.push_back(btn8); 
    //int defaultAlpha = btn0->alpha;
    btn0->clr.setHex(0xfff735, btn0->alpha);
    btn1->clr.setHex(0x0048fb, btn1->alpha);
    btn2->clr.setHex(0xea64ff, btn2->alpha);
    btn3->clr.setHex(0x9df11c, btn3->alpha);
    btn4->clr.setHex(0x6cf8fc, btn4->alpha);
    btn5->clr.setHex(0xd74040, btn5->alpha);
    btn6->clr.setHex(0xff7800, btn6->alpha);
    btn7->clr.setHex(0xff00e4, btn7->alpha);
    btn8->clr.setHex(0xccff00, btn8->alpha);
    
    // default button dimensions
    btnWidth = 200;
    btnHeight = 150;
    
}

void testApp::setupGUI() {
    
    // load gui xml settings
    settings.loadSettings("settings.xml", true, true);     
    settings.autoDraw();
    
    //settings.hide();
    
    int offsetX = 20;
    int offsetY = 20;
    int destWidth = 200;
    int destHeight = 25;
    
    //second column - paint
    int offsetX2 = 20;//230;
    
    // change this in the xml file to play a recording or switch to live. or just comment out and change in setup.
    settings.addFixedVar(&live, "live");
    
    // set the heading
    settings.addTitleText("Kinect Push Buttons", offsetX2, offsetY+5, destWidth);
    settings.addToggleButton("DRAW DEBUG", &debug, offsetX2, offsetY + 20, destWidth, destHeight);
    settings.addSlider("GRID SCALE", &gridScale, 0.0f, 2.0f, offsetX2, offsetY + 50, destWidth, destHeight);
    settings.addSlider("GRID SCALE FRICTION", &gridScaleFriction, 0, 1.0f, offsetX2, offsetY + 80, destWidth, destHeight);
    settings.addSlider("GRID HEIGHT RATIO", &gridHeightRatio, 0, 2.0f, offsetX2, offsetY + 110, destWidth, destHeight);
    settings.addSlider("ARM DEPTH RANGE Z", &armDepthRangeZ, 0, 600, offsetX2, offsetY + 140, destWidth, destHeight);
    settings.addSlider("COMBINED PRESS THRESHOLD", &combinedPressThreshold, 0, 2.0f, offsetX2, offsetY + 170, destWidth, destHeight);
    settings.addSlider("UPPER PRESS THRESHOLD", &upperPressThreshold, 0.0f, 1.0f, offsetX2, offsetY + 200, destWidth, destHeight);
    settings.addToggleButton("ALLOW MULTIPLE BUTTONS", &allowMultiplePresses, offsetX2, offsetY + 230, destWidth, destHeight);
    settings.addSlider("L ELBOW-HAND Z", &player.lowerLeftArmDistanceZ, 0.0f, 1.0f, offsetX2, offsetY + 260, destWidth, destHeight);
    settings.addSlider("L SHOULDER-ELBOW Z", &player.upperLeftArmDistanceZ, 0.0f, 1.0f, offsetX2, offsetY + 290, destWidth, destHeight);
    settings.addSlider("R ELBOW-HAND Z", &player.lowerRightArmDistanceZ, 0.0f, 1.0f, offsetX2, offsetY + 320, destWidth, destHeight);
    settings.addSlider("R SHOULDER-ELBOW Z", &player.upperRightArmDistanceZ, 0.0f, 1.0f, offsetX2, offsetY + 350, destWidth, destHeight);
    settings.addSlider("LEFT X", &normalisedLeft.x, 0.0f, 1.0f, offsetX2, offsetY + 380, destWidth, destHeight);
    settings.addSlider("LEFT Y", &normalisedLeft.y, 0, 1.0f, offsetX2, offsetY + 410, destWidth, destHeight);
    settings.addSlider("RIGHT X", &normalisedRight.x, 0.0f, 1.0f, offsetX2, offsetY + 440, destWidth, destHeight);
    settings.addSlider("RIGHT Y", &normalisedRight.y, 0, 1.0f, offsetX2, offsetY + 470, destWidth, destHeight);
        
    
    // button listeners
    ofxTouchGUIButton* resetBtn = settings.addButton("RESET", offsetX2, offsetY + 560, 97, destHeight);
    ofAddListener(resetBtn->onChangedEvent, this, &testApp::onButtonPressed); // bind a function to the element*/
    ofxTouchGUIButton* saveBtn = settings.addButton("SAVE", offsetX2 + 102, offsetY + 560, 97, destHeight); 
    ofAddListener(saveBtn->onChangedEvent, this, &testApp::onButtonPressed);

}

void testApp::onButtonPressed(const void* sender, string &buttonLabel) {
    
    // use the pointer to button or the label if lazy. 
    const ofxTouchGUIButton * button = (const ofxTouchGUIButton*)sender;
    
    //if( button == saveBtn) // using button pointer instead of label
    if(buttonLabel == "SAVE") {
        settings.saveSettings();
        cout << "SAVED" << endl;
    }
    else if(buttonLabel == "RESET") { 
        settings.resetDefaultValues();
    }
    
}



void testApp::exit() {
    
    openNI.waitForThread(true);
}

//--------------------------------------------------------------
void testApp::update(){
    
    //ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
	updateKinect();
    updateGrid();
 
}

void testApp::updateKinect() {
    
    openNI.update();
    playUser.update();
	if(bRecording){
		recorder.update();
	}
    
    int numUsers = playUser.getNumberOfTrackedUsers();
    //cout << playUser.needsPoseForCalibration() << endl;
    if(numUsers > 0) {
        usersDetected = true;
            
        // get nearest user
        float nearestZ; // = 5000;
        currentUserID = 0;
        for(int i = 0; i < numUsers; i++) {
            tracked = &playUser.getTrackedUser(i);
            ofPoint neckZ = tracked->getLimb(ofxOpenNIUser::Neck).end;
            if(i == 0){
                nearestZ = neckZ.z;
            } else if(neckZ.z < nearestZ){
                nearestZ = neckZ.z;
                currentUserID = i;
            }
        }        
        tracked = &playUser.getTrackedUser(currentUserID);

        
        // left hand
        player.leftHand = tracked->getLimb(ofxOpenNIUser::LeftLowerArm).end;
        player.leftHand.x = ofMap(player.leftHand.x, 0, 640, 0, stageWidth);
        player.leftHand.y = ofMap(player.leftHand.y, 0, 480, 0, stageHeight);
        
        // right hand
        player.rightHand = tracked->getLimb(ofxOpenNIUser::RightLowerArm).end;
        player.rightHand.x = ofMap(player.rightHand.x, 0, 640, 0, stageWidth);
        player.rightHand.y = ofMap(player.rightHand.y, 0, 480, 0, stageHeight);        
        
        // hips
        ofPoint hipLeft = tracked->getLimb(ofxOpenNIUser::Hip).begin;
        ofPoint hipRight = tracked->getLimb(ofxOpenNIUser::Hip).end;
        player.hips = hipLeft.middle(hipRight);
        player.hips.x = ofMap(player.hips.x, 0, 640, 0, stageWidth);
        player.hips.y = ofMap(player.hips.y, 0, 480, 0, stageHeight);
        
        // shoulders
        player.leftShoulder = tracked->getLimb(ofxOpenNIUser::LeftUpperArm).begin;
        player.leftShoulder.x = ofMap(player.leftShoulder.x, 0, 640, 0, stageWidth);
        player.leftShoulder.y = ofMap(player.leftShoulder.y, 0, 480, 0, stageHeight);
        player.rightShoulder = tracked->getLimb(ofxOpenNIUser::RightUpperArm).begin;
        player.rightShoulder.x = ofMap(player.rightShoulder.x, 0, 640, 0, stageWidth);
        player.rightShoulder.y = ofMap(player.rightShoulder.y, 0, 480, 0, stageHeight);
        
        // elbows
        player.leftElbow = tracked->getLimb(ofxOpenNIUser::LeftUpperArm).end;
        player.leftElbow.x = ofMap(player.leftElbow.x, 0, 640, 0, stageWidth);
        player.leftElbow.y = ofMap(player.leftElbow.y, 0, 480, 0, stageHeight);
        player.rightElbow = tracked->getLimb(ofxOpenNIUser::RightUpperArm).end;
        player.rightElbow.x = ofMap(player.rightElbow.x, 0, 640, 0, stageWidth);
        player.rightElbow.y = ofMap(player.rightElbow.y, 0, 480, 0, stageHeight);
        
        // neck
        player.neck = tracked->getLimb(ofxOpenNIUser::Neck).end;
        player.neck.x = ofMap(player.neck.x, 0, 640, 0, stageWidth);
        player.neck.y = ofMap(player.neck.y, 0, 480, 0, stageHeight);
        
        // work out armDepthRangeZ based on arm length - eg. left arm      
        ofPoint realLeftShoulder = openNI.projectiveToWorld(tracked->getLimb(ofxOpenNIUser::LeftUpperArm).begin);        
        ofPoint realLeftElbow = openNI.projectiveToWorld(tracked->getLimb(ofxOpenNIUser::LeftUpperArm).end);
        ofPoint realLeftHand = openNI.projectiveToWorld(tracked->getLimb(ofxOpenNIUser::LeftLowerArm).end);
        
        //float distA = realLeftShoulder.distance(realLeftElbow);
        //float distB = realLeftElbow.distance(realLeftHand);
        float armDistance = (realLeftShoulder.distance(realLeftElbow) + realLeftElbow.distance(realLeftHand)) * .5;
        //printf("\nreal dist xyz  %f %f", distA, distB);
        //armDepthRangeZ = (distA + distB) * .5; // average
        armDepthRangeZ += ( armDistance - armDepthRangeZ) * .03; // smoothed - hovers around 300 for me
        
        // constrain + normalise distance between joints based on 'armDepthRangeZ'
        player.lowerLeftArmDistanceZ =  CLAMP(player.leftElbow.z - player.leftHand.z, 0, armDepthRangeZ);
        player.lowerLeftArmDistanceZ = ofMap(player.lowerLeftArmDistanceZ, 0, armDepthRangeZ, 0.0f, 1.0f);
        player.upperLeftArmDistanceZ = CLAMP(player.leftShoulder.z - player.leftElbow.z, 0, armDepthRangeZ);
        player.upperLeftArmDistanceZ = ofMap(player.upperLeftArmDistanceZ, 0, armDepthRangeZ, 0.0f, 1.0f);
        
        player.lowerRightArmDistanceZ = CLAMP(player.rightElbow.z - player.rightHand.z, 0, armDepthRangeZ);
        player.lowerRightArmDistanceZ = ofMap(player.lowerRightArmDistanceZ, 0, armDepthRangeZ, 0.0f, 1.0f);        
        player.upperRightArmDistanceZ = CLAMP(player.rightShoulder.z - player.rightElbow.z, 0, armDepthRangeZ);
        player.upperRightArmDistanceZ = ofMap(player.upperRightArmDistanceZ, 0, armDepthRangeZ, 0.0f, 1.0f);
        
        // check if press occurs - combined distance for joints must be greater than 1 (combinedPressThreshold) & the shoulder-elbow must be more than 0.5 (upperPressThreshold);
        player.leftPressed = (player.lowerLeftArmDistanceZ + player.upperLeftArmDistanceZ > combinedPressThreshold && player.upperLeftArmDistanceZ > upperPressThreshold) ? true : false; 
        player.rightPressed = (player.lowerRightArmDistanceZ + player.upperRightArmDistanceZ > combinedPressThreshold && player.upperRightArmDistanceZ > upperPressThreshold) ? true : false;
        
        // button sizes are scaled according to torso length.
        int newBtnWidth = (player.hips.y - player.neck.y) * gridScale;
        btnWidth += (newBtnWidth - btnWidth) * gridScaleFriction;
        btnHeight = btnWidth * gridHeightRatio;
        
        
        
    } else {
        usersDetected = false;
    }
    
}

void testApp::updateGrid() {
    
    int spacer = 0;
    int rows = 3;
    
    gridOffsetX = ( (btnWidth + spacer) * 3 ) * .5;
    gridOffsetY = ( (btnHeight + spacer) * 3 ) * .5;
    
    // normalised hand positions based on grid size
    normalisedLeft = getNormalisedPosInside(player.leftHand, player.neck.x - gridOffsetX, player.neck.y - gridOffsetY, gridOffsetX * 2, gridOffsetY * 2);
    //cout << normalisedLeft.x << endl;
    
    normalisedRight= getNormalisedPosInside(player.rightHand, player.neck.x - gridOffsetX, player.neck.y - gridOffsetY, gridOffsetX * 2, gridOffsetY * 2);
    //cout << gridOffsetX * 2 << endl;
    
    for(int i = 0; i < btns.size(); i++) {
        
        GridButton * btn = btns[i];
        btn->update();
        
        // set grid positions
        int gridX = (btnWidth + spacer) * (i % 3) - gridOffsetX;
        int gridY = (btnHeight + spacer) * int(i / 3) - gridOffsetY;        
        btn->width = btnWidth;
        btn->height = btnHeight;
        btn->pos.x = player.neck.x + gridX;
        btn->pos.y = player.neck.y + gridY; // - (btnHeight * .5); // start grid from neck position
        
        // check if button/s activated
        if(allowMultiplePresses) {
            
            // allows multiple buttons to be activated from one press - eg. swiping/waving arms
            if(player.leftPressed) {
                btn->checkInside(player.leftHand);
            }
            
            if(player.rightPressed) {
                btn->checkInside(player.rightHand);
            }
            
        } else {
            
            // only 1 button activates per press.
            if(player.leftPressed && !player.isLeftAlreadyPressed) {
                if( btn->checkInside(player.leftHand) ) player.isLeftAlreadyPressed = true;
            } else if(!player.leftPressed && player.isLeftAlreadyPressed) {
                player.isLeftAlreadyPressed = false;
            }
            
            if(player.rightPressed && !player.isRightAlreadyPressed){
                if( btn->checkInside(player.rightHand) ) player.isRightAlreadyPressed = true;
            } else if(!player.rightPressed && player.isRightAlreadyPressed) {
                player.isRightAlreadyPressed = false;
            }
        }
        
        
    }
}

ofPoint testApp::getNormalisedPosInside(ofPoint hitPoint, float x, float y, float w, float h) {
    
    //float nx = x;// + w; // hack
    //float ny = y;// + h; // hack
    ofPoint pos;
    //bool isInside = nx >= hitPoint.x && nx <= hitPoint.x + w && ny >= hitPoint.y && ny <= hitPoint.y + h;
    pos.x = CLAMP((hitPoint.x - x) / w, 0.0f, 1.0f);
    pos.y = CLAMP((hitPoint.y - y) / h, 0.0f, 1.0f);
    
    return pos;
}


//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(38);

    //ofSetColor(0,255,220,255);
    //ofSetColor(255,0,228,255);
    ofSetColor(255,255,255,255);
    ofEnableAlphaBlending();
	openNI.draw(0,0, stageWidth, stageHeight);
    
    ofSetColor(255,255,255,255);
    if(usersDetected) drawGrid();
    if(debug) drawDebug(); 
}

void testApp::drawDebug(){
    
    if(usersDetected) {
        //tracked->debugDraw();
        
        
        ofSetColor(255, maxSkeletonAlpha);
        
        //ofFill();
        // circles on main 3 points
        if(player.leftPressed) {
            ofFill();
            ofCircle(player.leftHand.x, player.leftHand.y, 20);
        } else {
            ofNoFill();
            ofCircle(player.leftHand.x, player.leftHand.y, 10);
        }
        if(player.rightPressed) {
            ofFill();
            ofCircle(player.rightHand.x, player.rightHand.y, 20);
        } else {
            ofNoFill();
            ofCircle(player.rightHand.x, player.rightHand.y, 10);
        }
        
        
        ofNoFill();
        
        //ofCircle(player.center.x, player.center.y, 10);
        
        // triangle between main 3 points
        ofSetColor(255, maxSkeletonAlpha);
        
        // draw hands to neck
        //ofTriangle(player.leftHand.x , player.leftHand.y , player.neck.x , player.neck.y , player.rightHand.x , player.rightHand.y);
        
        //ofSetLineWidth(2.0f);
        
        // draw shoulders to hips
        ofTriangle(player.leftShoulder.x, player.leftShoulder.y, player.hips.x, player.hips.y, player.rightShoulder.x,player.rightShoulder.y);
        
        // left side
        ofTriangle(player.leftHand.x, player.leftHand.y, player.leftElbow.x, player.leftElbow.y, player.leftShoulder.x,player.leftShoulder.y);
        
        // right side
        ofTriangle(player.rightHand.x, player.rightHand.y, player.rightElbow.x, player.rightElbow.y, player.rightShoulder.x,player.rightShoulder.y);
        
        
    }
    
}



 

void testApp::drawGrid(){

    ofFill();
    for(int i = 0; i < btns.size(); i++) btns[i]->draw();

}





//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if(key == 'R'){
		bRecording = !bRecording;
		if(bRecording){
			recorder.setup(openNI,"recording.oni");
			recorder.startCapture();
            cout << "recording" << endl;
		}else{
			recorder.stopCapture();
            cout << "stopped recording" << endl;
		}
	} else if(key == ' '){
        settings.toggleDisplay();
    } 
    
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

