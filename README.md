![https://github.com/trentbrooks/KinectPushButtons/raw/master/screenshot1.jpg](https://github.com/trentbrooks/KinectPushButtons/raw/master/screenshot1.jpg)
## About ##
Sample Openframeworks project for creating a GUI for Kinect applications (current sample shows push buttons). Uses OpenNI for auto calibration.

We track the nearest player and draw a 3 x 3 grid of buttons which move and scale according to the player's size and position. Press/release achieved by measuring the z-depth distance between the arm joints (shoulder to elbow, and elbow to hand) for each arm. Then we work out the ratios as a percentage of the player's size (I used the torso).

A version of this was used at the Sydney Vivid Festival 2012, for 'The Collaboration' project with Will.I.Am: [http://vimeo.com/45629975](http://vimeo.com/45629975)

## Openframeworks addons required ##
*   ofxOpenNI2: https://github.com/arturoc/ofxOpenNI2
*   ofxTouchGUI: https://github.com/trentbrooks/ofxTouchGUI
* 	ofxXmlSettings & ofxOsc (in addons folder)

-Trent Brooks