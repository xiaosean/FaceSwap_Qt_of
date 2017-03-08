#include "ofApp.h"
#ifndef __OPTIMIZE__
    ofSetColor(ofColor::red);
    ofDrawBitmapString("Warning! Run this app in release mode to get proper performance!",10,60);
    ofSetColor(ofColor::white);
#endif

//--------------------------------------------------------------
void ofApp::setup(){
    // All examples share data files from example-data, so setting data path to this folder
    // This is only relevant for the example apps
    ofSetDataPathRoot(ofFile(__BASE_FILE__).getEnclosingDirectory()+"../../model/");
    // Setup grabber
    grabber.setup(IMG_WIDTH,IMG_HEIGHT);
    grabber.setDesiredFrameRate(30);
    std::string adma_path = "/home/spark/Desktop/FaceSwap_Qt_of/adam.png";
    std::string man_path = "/home/spark/Desktop/FaceSwap_Qt_of/man1.jpg";
    std::string girl_path = "/home/spark/Desktop/face_Detect/girl2.jpg";
    img_2.load(adma_path);
    img_2.resize(IMG_WIDTH,IMG_HEIGHT);
    img2 = toCv(img_2.getPixelsRef());


}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    if(grabber.isFrameNew())
        toOf(fs.swap(toCv(grabber.getPixelsRef()), img2), swapImage);
}

//--------------------------------------------------------------
void ofApp::draw(){
    _count++;

    // Draw camera image
    grabber.draw(0, 0);
//    tracker.drawDebug();

//    img_1.draw(0, 0);
    img_2.draw(0, 300);
    // 0~67 points can see the point
     // https://www.google.com.tw/search?q=DLIB+LANDMARKS&espv=2&biw=998&bih=356&source=lnms&tbm=isch&sa=X&ved=0ahUKEwjslqihp_7QAhXJNJQKHblWB84Q_AUIBigB#imgrc=XfSi6XDndzX5zM%3A
    swapImage.setImageType(OF_IMAGE_COLOR);
    swapImage.resize(600,430);
    swapImage.draw(350,0);

}



