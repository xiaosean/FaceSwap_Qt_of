#include "ofApp.h"


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

//    if(!img_1.load(filename)) {
//        display_file_path(filename);
//    }
//    triList =
//    ifstream ifs("/home/spark/Desktop/learnopencv/FaceMorph/tri.txt");
//    int x,y,z;
//    while(ifs >> x >> y >> z){
//        triVector.push_back(x);
//        triVector.push_back(y);
//        triVector.push_back(z);

//    }
    img_1.load(man_path);
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
    imgMorph = Mat::zeros(img1.size(), CV_32FC3);
//    faceswap fs(img2);




}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();

//     Update tracker when there are new frames
    if(grabber.isFrameNew()){
        cout<< "grabber update" << std::endl;

//        tracker.update(grabber);
        faceTracker1.update(img_1);
//        faceTracker1.update(grabber);
        faceTracker2.update(img_2);
    }
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
    img_2.draw(600, 100);



    faceTracker1.drawDebug();
//    faceTracker1.drawDebugPose();
//    faceTracker1.
    std::vector<ofxFaceTracker2Instance> faceTracker1_faces = faceTracker1.getInstances();
    std::vector<ofxFaceTracker2Instance> faceTracker2_faces = faceTracker2.getInstances();
    cout<< "face1 vec size = "<< faceTracker1_faces.size() << std::endl;
    cout<< "face2 vec size = "<< faceTracker2_faces.size() << std::endl;
    // 0~67 points can see the point
     // https://www.google.com.tw/search?q=DLIB+LANDMARKS&espv=2&biw=998&bih=356&source=lnms&tbm=isch&sa=X&ved=0ahUKEwjslqihp_7QAhXJNJQKHblWB84Q_AUIBigB#imgrc=XfSi6XDndzX5zM%3A

    // if u wants to draw triangle maybe you can see ofxFaceTracker2Landmarks.cpp
    // ofMesh ofxFaceTracker2Landmarks::getMesh(vector<T> points) const/*
//    int pointNum = 67;
    if(faceTracker1_faces.size() > 0 && faceTracker2_faces.size() > 0){
        ofxFaceTracker2Landmarks faceLm_1 = faceTracker1_faces.at(0).getLandmarks();
        std::cout << "start swap"<<endl;
        Mat grabberMat = toCv(grabber.getPixelsRef());
//        Mat output = fs.swap(faceTracker1, faceTracker2, grabberMat, img2);
        Mat output = fs.swap(faceTracker1, faceTracker2, img1, img2);
        std::cout<<"output col" << output.cols << std::endl;

//        output.
        ofFloatImage  swapImage;
//        imshow("Morphed Face", output);
//        waitKey(0);

        toOf(output, swapImage);
        swapImage.draw(900,100);
        std::cout<<"draw swapImage" << std::endl;

//        imshow("Face Swapped", output);
//        std::cout<<"draw Face" << std::endl;

//        waitKey(0);
//        destroyAllWindows();



        //        ofVec2f face1_point = faceLm_1.getImagePoint(pointNum);
        //        cout<< "face1 pointNum = "<< pointNum << "point.x = " << face1_point.x << "point.y = " << face1_point.y << std::endl;
        //        ofxFaceTracker2Landmarks faceLm_2 = faceTracker2_faces.at(0).getLandmarks();
        //        ofVec2f face2_point = faceLm_2.getImagePoint(pointNum);
        //        cout<< "face2 pointNum = "<< pointNum << "point.x = " << face2_point.x << "point.y = " << face2_point.y << std::endl;
        //show debugs line
//        drawDebug_Triangle_1(getTrianglePointVec(faceLm_1.getCvImagePoints()));


//        vector<Point2f> src_points = faceLm_1.getCvImagePoints();
//        vector<Point2f> dest_points = faceLm_2.getCvImagePoints();
//        vector<Point2f> out_points;

//        //compute weighted average point coordinates
//        for(int i = 0; i < src_points.size(); i++)
//        {
//            float x, y;
//            x = (1 - alpha) * src_points[i].x + alpha * dest_points[i].x;
//            y =  ( 1 - alpha ) * src_points[i].y + alpha * dest_points[i].y;

//            out_points.push_back(Point2f(x,y));

//        }


//        //Read triangle indices
//        int x,y,z;

//        for(int i = 0; i < triVector.size(); i+=3)
//        {
//            x = triVector[i];
//            y = triVector[i + 1];
//            z = triVector[i + 2];
//            // Triangles
//            vector<Point2f> t1, t2, t;

//            // Triangle corners for image 1.
//            t1.push_back( src_points[x] );
//            t1.push_back( src_points[y] );
//            t1.push_back( src_points[z] );

//            // Triangle corners for image 2.
//            t2.push_back( dest_points[x] );
//            t2.push_back( dest_points[y] );
//            t2.push_back( dest_points[z] );

//            // Triangle corners for morphed image.
//            t.push_back( out_points[x] );
//            t.push_back( out_points[y] );
//            t.push_back( out_points[z] );
//            morphTriangle(img1, img2, imgMorph, t1, t2, t, alpha);
//        }

        // Display Result
//        imshow("Morphed Face", imgMorph / 255.0);
//        waitKey(0);
    }
}


    //Read points


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
