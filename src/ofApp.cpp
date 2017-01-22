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
    grabber.setup(360,480);
//    ofLoadImage(img_1, "./man1.png");
//    ofLoadImage(img_2, "/home/spark/Desktop/FaceSwap_Qt_of/adam.png");
    std::string adma_path = "/home/spark/Desktop/FaceSwap_Qt_of/adam.png";
    std::string man_path = "/home/spark/Desktop/FaceSwap_Qt_of/man1.jpg";
    std::string girl_path = "/home/spark/Desktop/face_Detect/girl2.jpg";
    img_1.load(man_path);
//    img_1.load(girl_path);
    img_2.load(adma_path);
    img_1.resize(IMG_WIDTH,IMG_HEIGHT);
    img_2.resize(IMG_WIDTH,IMG_HEIGHT);

    // Setup tracker
    faceTracker1.setup();
    faceTracker2.setup();
//    tracker.setup();
    //alpha controls the degree of morph
    //Read input images
    img1 = toCv(img_1.getPixelsRef());
    img2 = toCv(img_2.getPixelsRef());
    //convert Mat to float data type
//    img1.convertTo(img1, CV_32F);
//    img2.convertTo(img2, CV_32F);
    //empty average image
//    imshow("img2 Face", img2);
//    waitKey(0);
//    destroyAllWindows();
//    imgMorph = Mat::zeros(img1.size(), CV_32FC3);
//    faceswap fs(img2);




}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();

//     Update tracker when there are new frames
//    if(grabber.isFrameNew()){
//        cout<< "grabber update" << std::endl;

//        tracker.update(grabber);
//        faceTracker1.update(img_1);
//        faceTracker1.update(grabber);
//        faceTracker2.update(img_2);
//    }
    faceTracker1.update(img_1);
    faceTracker2.update(img_2);

}

//--------------------------------------------------------------
void ofApp::draw(){
    _count++;

    std::cout<< "draw  = " << _count << std::endl;


    // Draw camera image
//    grabber.draw(0, 0);
    img_1.draw(0, 0);
    img_2.draw(600, 0);



    faceTracker1.drawDebug();
//    faceTracker1.drawDebugPose();
//    faceTracker1.
    std::vector<ofxFaceTracker2Instance> faceTracker1_faces = faceTracker1.getInstances();
    std::vector<ofxFaceTracker2Instance> faceTracker2_faces = faceTracker2.getInstances();
    // 0~67 points can see the point
     // https://www.google.com.tw/search?q=DLIB+LANDMARKS&espv=2&biw=998&bih=356&source=lnms&tbm=isch&sa=X&ved=0ahUKEwjslqihp_7QAhXJNJQKHblWB84Q_AUIBigB#imgrc=XfSi6XDndzX5zM%3A

    // if u wants to draw triangle maybe you can see ofxFaceTracker2Landmarks.cpp
    // ofMesh ofxFaceTracker2Landmarks::getMesh(vector<T> points) const/*
//    int pointNum = 67;
    if(faceTracker1_faces.size() > 0 && faceTracker2_faces.size() > 0){
        ofxFaceTracker2Landmarks faceLm_1 = faceTracker1_faces.at(0).getLandmarks();
        Mat grabberMat = toCv(grabber.getPixelsRef());
//        Mat output = fs.swap(faceTracker1, faceTracker2, grabberMat, img2);
        Mat output = fs.swap(faceTracker1, faceTracker2, img1, img2);

//        output.
        ofFloatImage  swapImage;
//        ofImage  swapImage;
//        imshow("Morphed Face", output);
//        waitKey(0);
        toOf(output, swapImage);
        swapImage.setImageType(OF_IMAGE_COLOR);
        swapImage.draw(900,0);

    }
}



