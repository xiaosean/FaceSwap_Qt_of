#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    // All examples share data files from example-data, so setting data path to this folder
    // This is only relevant for the example apps
    ofSetDataPathRoot(ofFile(__BASE_FILE__).getEnclosingDirectory()+"../../model/");
    // Setup grabber
//    grabber.setup(480,300);
//    ofLoadImage(img_1, "./man1.png");
//    ofLoadImage(img_2, "/home/spark/Desktop/FaceSwap_Qt_of/adam.png");
    std::string adma_path = "/home/spark/Desktop/FaceSwap_Qt_of/adam.png";
    std::string man_path = "/home/spark/Desktop/FaceSwap_Qt_of/man1.jpg";

//    if(!img_1.load(filename)) {
//        display_file_path(filename);
//    }
    img_1.load(man_path);
    img_2.load(adma_path);
    img_1.resize(IMG_WIDTH,IMG_HEIGHT);
    img_2.resize(IMG_WIDTH,IMG_HEIGHT);

    // Setup tracker
//    tracker.setup();
    faceTracker1.setup();
    faceTracker2.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
//    grabber.update();
    
    // Update tracker when there are new frames
//    if(grabber.isFrameNew()){
//        tracker.update(grabber);
//    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    // Draw camera image
    img_1.draw(100, 100);
    //    img_1.draw(100, 100);
    img_2.draw(400, 100);

    faceTracker1.update(img_1);
    faceTracker2.update(img_2);

//    faceTracker1.drawDebug();
//    faceTracker1.drawDebugPose();
//    faceTracker1.
    vector<ofxFaceTracker2Instance> faceTracker1_faces = faceTracker1.getInstances();
    vector<ofxFaceTracker2Instance> faceTracker2_faces = faceTracker2.getInstances();
    cout<< "face1 vec size = "<< faceTracker1_faces.size() << std::endl;
    cout<< "face2 vec size = "<< faceTracker2_faces.size() << std::endl;
    // 0~67 points can see the point
     // https://www.google.com.tw/search?q=DLIB+LANDMARKS&espv=2&biw=998&bih=356&source=lnms&tbm=isch&sa=X&ved=0ahUKEwjslqihp_7QAhXJNJQKHblWB84Q_AUIBigB#imgrc=XfSi6XDndzX5zM%3A

    // if u wants to draw triangle maybe you can see ofxFaceTracker2Landmarks.cpp
    // ofMesh ofxFaceTracker2Landmarks::getMesh(vector<T> points) const
    int pointNum = 67;
    if(faceTracker1_faces.size() > 0){
        ofxFaceTracker2Landmarks faceLm_1 = faceTracker1_faces.at(0).getLandmarks();
        ofVec2f face1_point = faceLm_1.getImagePoint(pointNum);
        cout<< "face1 pointNum = "<< pointNum << "point.x = " << face1_point.x << "point.y = " << face1_point.y << std::endl;
//        img_1.setColor(face1_point.x-1, face1_point.y-1, ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
//        img_1.setColor(face1_point.x-1, face1_point.y, ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
//        img_1.setColor(face1_point.x-1, face1_point.y+1, ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
//        img_1.setColor(face1_point.x, face1_point.y-1, ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
//        img_1.setColor(face1_point.x, face1_point.y, ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
//        img_1.setColor(face1_point.x, face1_point.y+1, ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
//        img_1.setColor(face1_point.x+1, face1_point.y-1, ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
//        img_1.setColor(face1_point.x+1, face1_point.y, ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
//        img_1.setColor(face1_point.x+1, face1_point.y+1, ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
//        img_1.update();

        //show debugs line
        drawDebug_Triangle_1(getTrianglePointVec(faceLm_1.getCvImagePoints()));
    }
    if(faceTracker2_faces.size() > 0){
        ofxFaceTracker2Landmarks faceLm_2 = faceTracker2_faces.at(0).getLandmarks();
        ofVec2f face2_point = faceLm_2.getImagePoint(pointNum);
        cout<< "face2 pointNum = "<< pointNum << "point.x = " << face2_point.x << "point.y = " << face2_point.y << std::endl;
        drawDebug_Triangle_2(getTrianglePointVec(faceLm_2.getCvImagePoints()));

    }

//    ofDrawLine(10,10,100,100);

//    faceTracker1.draw(100, 100);


//    grabber.draw(600, 0);
    
    // Draw tracker landmarks
//    tracker.drawDebug();
    
    // Draw estimated 3d pose
//    tracker.drawDebugPose();
    
    // Draw text UI
//    ofDrawBitmapStringHighlight("Framerate : "+ofToString(ofGetFrameRate()), 10, 20);
//    ofDrawBitmapStringHighlight("Tracker thread framerate : "+ofToString(tracker.getThreadFps()), 10, 40);
    
#ifndef __OPTIMIZE__
    ofSetColor(ofColor::red);
    ofDrawBitmapString("Warning! Run this app in release mode to get proper performance!",10,60);
    ofSetColor(ofColor::white);
#endif
}
void ofApp::drawDebug_Triangle_1(vector<cv::Vec6f>triangleList){
    for( size_t i = 0; i < triangleList.size(); i++ )
    {
        cv::Vec6f t = triangleList[i];
        cv::Point2f pt1 = cv::Point(cvRound(t[0]), cvRound(t[1]));
        cv::Point2f pt2 = cv::Point(cvRound(t[2]), cvRound(t[3]));
        cv::Point2f pt3 = cv::Point(cvRound(t[4]), cvRound(t[5]));

        ofSetColor(255,255,255);
        if(i == 5 || i == 11 || i == 15)
            ofSetColor(0, 0, 255);//set te color to blue
        ofDrawLine(IMG1_WIDTH_EDGE + pt1.x, IMG1_HEIGHT_EDGE + pt1.y,IMG1_WIDTH_EDGE + pt2.x,  IMG1_HEIGHT_EDGE + pt2.y);
        ofDrawLine(IMG1_WIDTH_EDGE + pt2.x, IMG1_HEIGHT_EDGE + pt2.y,IMG1_WIDTH_EDGE + pt3.x, IMG1_HEIGHT_EDGE + pt3.y);
        ofDrawLine(IMG1_WIDTH_EDGE + pt3.x, IMG1_HEIGHT_EDGE + pt3.y,IMG1_WIDTH_EDGE + pt1.x, IMG1_HEIGHT_EDGE + pt1.y);
    }
}
void ofApp::drawDebug_Triangle_2(vector<cv::Vec6f>triangleList){
    for( size_t i = 0; i < triangleList.size(); i++ )
    {
        cv::Vec6f t = triangleList[i];
        cv::Point2f pt1 = cv::Point(cvRound(t[0]), cvRound(t[1]));
        cv::Point2f pt2 = cv::Point(cvRound(t[2]), cvRound(t[3]));
        cv::Point2f pt3 = cv::Point(cvRound(t[4]), cvRound(t[5]));

        ofSetColor(255,255,255);
        if(i == 5 || i == 11 || i == 15)
            ofSetColor(0, 0, 255);//set te color to blue
        ofDrawLine(IMG2_WIDTH_EDGE + pt1.x, IMG2_HEIGHT_EDGE + pt1.y,IMG2_WIDTH_EDGE + pt2.x,  IMG2_HEIGHT_EDGE + pt2.y);
        ofDrawLine(IMG2_WIDTH_EDGE + pt2.x, IMG2_HEIGHT_EDGE + pt2.y,IMG2_WIDTH_EDGE + pt3.x, IMG2_HEIGHT_EDGE + pt3.y);
        ofDrawLine(IMG2_WIDTH_EDGE + pt3.x, IMG2_HEIGHT_EDGE + pt3.y,IMG2_WIDTH_EDGE + pt1.x, IMG2_HEIGHT_EDGE + pt1.y);
    }
}
template <class T>
vector<cv::Vec6f> ofApp::getTrianglePointVec(vector<T> points) const {
    cv::Rect rect(0, 0, IMG_WIDTH, IMG_HEIGHT);
    cv::Subdiv2D subdiv(rect);

    for(int i=0;i<points.size();i++){
        if( rect.contains(points[i]) ){
            subdiv.insert(points[i]);
        }
    }
    vector<cv::Vec6f> triangleList;
    subdiv.getTriangleList(triangleList);
    return(triangleList);
}
