// ofxFaceTrack2 example: SIMPLE EXAMPLE
//
// This example shows minimal usage of the ofxFaceTracker2 addon,
// doing simple landmark detection and pose estimation
//

#pragma once

#include "ofxFaceTracker2.h"
using namespace ofxCv;
using namespace cv;


class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void drawDebug_Triangle_1(vector<cv::Vec6f>triangleList);
    void drawDebug_Triangle_2(vector<cv::Vec6f>triangleList);
    void applyAffineTransform(Mat &warpImage, Mat &src, vector<Point2f> &srcTri, vector<Point2f> &dstTri);
    void morphTriangle(Mat &img1, Mat &img2, Mat &img, vector<Point2f> &t1, vector<Point2f> &t2, vector<Point2f> &t, double alpha);

    template <class T>
    vector<cv::Vec6f>getTrianglePointVec(vector<T>points) const;

    ofxFaceTracker2 tracker;
    ofxFaceTracker2 faceTracker1;
    ofxFaceTracker2 faceTracker2;

    ofVideoGrabber grabber;
    ofImage img_1;
    ofImage img_2;
    Mat img1;
    Mat img2;
    Mat imgMorph;
private:
    int IMG1_WIDTH_EDGE = 100;
    int IMG1_HEIGHT_EDGE = 100;
    int IMG2_WIDTH_EDGE = 400;
    int IMG2_HEIGHT_EDGE = 100;
    int IMG_WIDTH = 240;
    int IMG_HEIGHT = 320;
    double alpha = 0.5;
    vector<int> triVector;
};
