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
    void drawDebug_Triangle_1(vector<cv::Vec6f>triangleList);
    void drawDebug_Triangle_2(vector<cv::Vec6f>triangleList);

    template <class T>
    vector<cv::Vec6f>getTrianglePointVec(vector<T>points) const;

    ofxFaceTracker2 tracker;
    ofxFaceTracker2 faceTracker1;
    ofxFaceTracker2 faceTracker2;

    ofVideoGrabber grabber;
    ofImage img_1;
    ofImage img_2;
private:
    int IMG1_WIDTH_EDGE = 100;
    int IMG1_HEIGHT_EDGE = 100;
    int IMG2_WIDTH_EDGE = 400;
    int IMG2_HEIGHT_EDGE = 100;
    int IMG_WIDTH = 240;
    int IMG_HEIGHT = 320;
};
