// ofxFaceTrack2 example: SIMPLE EXAMPLE
//
// This example shows minimal usage of the ofxFaceTracker2 addon,
// doing simple landmark detection and pose estimation
//

#pragma once

//#include "ofxFaceTracker2.h"
#include "faceswap.h"

using namespace ofxCv;
using namespace cv;
using namespace std;


class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void drawDebug_Triangle_1(std::vector<cv::Vec6f>triangleList);
    void drawDebug_Triangle_2(std::vector<cv::Vec6f>triangleList);
    void applyAffineTransform(Mat &warpImage, Mat &src, std::vector<Point2f> &srcTri, std::vector<Point2f> &dstTri);
    void morphTriangle(Mat &img1, Mat &img2, Mat &img, std::vector<Point2f> &t1, std::vector<Point2f> &t2, std::vector<Point2f> &t, double alpha);
    template <class T>
    std::vector<cv::Vec6f>getTrianglePointVec(std::vector<T>points) const;

    ofVideoGrabber grabber;
    ofImage img_1;
    ofImage img_2;
    Mat img1;
    Mat img2;
    Mat imgMorph;
    ofFloatImage  swapImage;

private:
    int IMG_WIDTH = 300;
    int IMG_HEIGHT = 260;
    faceswap fs;
    int _count = 0;
   //use skip frame to speed up frame
    int _skipFrame = 3;
};
