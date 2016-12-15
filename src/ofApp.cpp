#include "ofApp.h"

void ofApp::xiaoDrawPoint(){
    vector<ofxFaceTracker2Instance> faces = tracker.getInstances();
    for(auto face :faces){
        int pointNum = 0;
//        vector<cv::Point2f> facePoints = face.getLandmarks().getCvImagePoints();
        ofVec2f point = face.getLandmarks().getImagePoint(0);
        cout<< "pointNum = "<< pointNum << "point.x = " << point.x << "point.y = " << point.y << std::endl;

    }
//    int pointCount = 0;
//    for(cv::Point2f point :facePoints){
//        cout<< "pointCount = "<< pointCount << "point.x = " << point;
//    }

}
//--------------------------------------------------------------
void ofApp::setup(){
    // All examples share data files from example-data, so setting data path to this folder
    // This is only relevant for the example apps
    ofSetDataPathRoot(ofFile(__BASE_FILE__).getEnclosingDirectory()+"../../model/");
    
    // Setup grabber
    grabber.setup(1280,720);
    
    // Setup tracker
    tracker.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    
    // Update tracker when there are new frames
    if(grabber.isFrameNew()){
        tracker.update(grabber);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw camera image
    grabber.draw(0, 0);
    // Draw tracker landmarks
    tracker.drawDebug();
    // Draw estimated 3d pose
    tracker.drawDebugPose();
    
    // Draw text UI
    ofDrawBitmapStringHighlight("Framerate : "+ofToString(ofGetFrameRate()), 10, 20);
    ofDrawBitmapStringHighlight("Tracker thread framerate : "+ofToString(tracker.getThreadFps()), 10, 40);
    
#ifndef __OPTIMIZE__
    ofSetColor(ofColor::red);
    ofDrawBitmapString("Warning! Run this app in release mode to get proper performance!",10,60);
    ofSetColor(ofColor::white);
#endif
    xiaoDrawPoint();

}
