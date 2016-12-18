// ofxFaceTrack2 example: SIMPLE EXAMPLE
//
// This example shows minimal usage of the ofxFaceTracker2 addon,
// doing simple landmark detection and pose estimation
//

#pragma once

#include "ofMain.h"
#include "ofxFaceTracker2.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    ofxFaceTracker2 tracker;
    ofxFaceTracker2 faceTracker1;
    ofxFaceTracker2 faceTracker2;

    ofVideoGrabber grabber;
    ofImage img_1;
    ofImage img_2;
};
