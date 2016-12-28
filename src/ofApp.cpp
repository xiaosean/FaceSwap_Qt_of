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
//    triList =
    ifstream ifs("/home/spark/Desktop/learnopencv/FaceMorph/tri.txt");
    int x,y,z;
    while(ifs >> x >> y >> z){
        triVector.push_back(x);
        triVector.push_back(y);
        triVector.push_back(z);

    }
    img_1.load(man_path);
    img_2.load(adma_path);
    img_1.resize(IMG_WIDTH,IMG_HEIGHT);
    img_2.resize(IMG_WIDTH,IMG_HEIGHT);

    // Setup tracker
//    tracker.setup();
    faceTracker1.setup();
    faceTracker2.setup();
    tracker.setup();
    //alpha controls the degree of morph
    //Read input images
    img1 = toCv(img_1);
    img2 = toCv(img_2);
    //convert Mat to float data type
    img1.convertTo(img1, CV_32F);
    img2.convertTo(img2, CV_32F);
    //empty average image
    imgMorph = Mat::zeros(img1.size(), CV_32FC3);




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
    if(faceTracker1_faces.size() > 0 && faceTracker2_faces.size() > 0){
        ofxFaceTracker2Landmarks faceLm_1 = faceTracker1_faces.at(0).getLandmarks();
        ofVec2f face1_point = faceLm_1.getImagePoint(pointNum);
        cout<< "face1 pointNum = "<< pointNum << "point.x = " << face1_point.x << "point.y = " << face1_point.y << std::endl;
        ofxFaceTracker2Landmarks faceLm_2 = faceTracker2_faces.at(0).getLandmarks();
        ofVec2f face2_point = faceLm_2.getImagePoint(pointNum);
        cout<< "face2 pointNum = "<< pointNum << "point.x = " << face2_point.x << "point.y = " << face2_point.y << std::endl;
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

// Apply affine transform calculated using srcTri and dstTri to src
void ofApp::applyAffineTransform(Mat &warpImage, Mat &src, vector<Point2f> &srcTri, vector<Point2f> &dstTri)
{

    // Given a pair of triangles, find the affine transform.
    Mat warpMat = getAffineTransform( srcTri, dstTri );

    // Apply the Affine Transform just found to the src image
    warpAffine( src, warpImage, warpMat, warpImage.size(), INTER_LINEAR, BORDER_REFLECT_101);
}

// Warps and alpha blends triangular regions from img1 and img2 to img
void ofApp::morphTriangle(Mat &img1, Mat &img2, Mat &img, vector<Point2f> &t1, vector<Point2f> &t2, vector<Point2f> &t, double alpha)
{

    // Find bounding rectangle for each triangle
    Rect r = boundingRect(t);
    Rect r1 = boundingRect(t1);
    Rect r2 = boundingRect(t2);

    // Offset points by left top corner of the respective rectangles
    vector<Point2f> t1Rect, t2Rect, tRect;
    vector<Point> tRectInt;
    for(int i = 0; i < 3; i++)
    {
        tRect.push_back( Point2f( t[i].x - r.x, t[i].y -  r.y) );
        tRectInt.push_back( Point(t[i].x - r.x, t[i].y - r.y) ); // for fillConvexPoly

        t1Rect.push_back( Point2f( t1[i].x - r1.x, t1[i].y -  r1.y) );
        t2Rect.push_back( Point2f( t2[i].x - r2.x, t2[i].y - r2.y) );
    }

    // Get mask by filling triangle
    Mat mask = Mat::zeros(r.height, r.width, CV_32FC3);
    fillConvexPoly(mask, tRectInt, Scalar(1.0, 1.0, 1.0), 16, 0);

    // Apply warpImage to small rectangular patches
    Mat img1Rect, img2Rect;
    img1(r1).copyTo(img1Rect);
    img2(r2).copyTo(img2Rect);

    Mat warpImage1 = Mat::zeros(r.height, r.width, img1Rect.type());
    Mat warpImage2 = Mat::zeros(r.height, r.width, img2Rect.type());

    applyAffineTransform(warpImage1, img1Rect, t1Rect, tRect);
    applyAffineTransform(warpImage2, img2Rect, t2Rect, tRect);

    // Alpha blend rectangular patches
    Mat imgRect = (1.0 - alpha) * warpImage1 + alpha * warpImage2;

    // Copy triangular region of the rectangular patch to the output image
    multiply(imgRect,mask, imgRect);
    multiply(img(r), Scalar(1.0,1.0,1.0) - mask, img(r));
    img(r) = img(r) + imgRect;


}
