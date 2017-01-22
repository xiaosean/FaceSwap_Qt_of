// ofxFaceTrack2 example: SIMPLE EXAMPLE
//
// This example shows minimal usage of the ofxFaceTracker2 addon,
// doing simple landmark detection and pose estimation
//

#pragma once

#include "ofxFaceTracker2.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include "ofxCv.h"
//#include <dlib/opencv.h>
//#include <dlib/image_processing/frontal_face_detector.h>
//#include <dlib/image_processing/render_face_detections.h>
//#include <dlib/image_processing.h>
//#include <dlib/gui_widgets.h>

#define FACE_DOWNSAMPLE_RATIO 2
#define SKIP_FRAMES 4
using namespace dlib;
using namespace ofxCv;
using namespace cv;


class faceswap{
    typedef struct _TRIANGLE_DESC_
    {
        long pt1, pt2, pt3;
        _TRIANGLE_DESC_(const long _pt1, long _pt2, const long _pt3) :
            pt1(_pt1), pt2(_pt2), pt3(_pt3) {}
    }TRIANGLE_DESC;

public:
    faceswap();
//    faceswap(Mat swapModel);
//    faceswap(Mat getImg1, Mat getImg2);
    ~faceswap();
//    Mat getMorphFace();
//    Mat swap(Mat src);
//    Mat swap(ofxFaceTracker2& faceTracker1, ofxFaceTracker2& faceTracker2, Mat src);
    Mat swap(Mat src, Mat iminateModel);
    Mat swap(ofxFaceTracker2& faceTracker1, ofxFaceTracker2& faceTracker2, Mat src, Mat swapModel);
    Mat convexSwap(Mat src, Mat swapModel);
    Mat convexSwap(ofxFaceTracker2& faceTracker1, ofxFaceTracker2& faceTracker2, Mat src, Mat swapModel);
    Mat morphSwap(ofxFaceTracker2& faceTracker1, ofxFaceTracker2& faceTracker2, Mat src, Mat swapModel);

//    Mat swap(Mat src, Mat swapModel);
    ofxFaceTracker2 faceTracker1;
    ofxFaceTracker2 faceTracker2;
    ofImage img_1;
    ofImage img_2;
    Mat img1;
    Mat img2;
private:
    int IMG1_WIDTH_EDGE = 100;
    int IMG1_HEIGHT_EDGE = 100;
    int IMG2_WIDTH_EDGE = 400;
    int IMG2_HEIGHT_EDGE = 100;
    int IMG_WIDTH = 240;
    int IMG_HEIGHT = 320;
    int _count = 0;
    double alpha = 0.5;
    std::vector<TRIANGLE_DESC> triList;
    std::vector<std::vector<int>> triVec;
    std::vector<cv::Point2f> EXpoints;
    std::vector<Point2f> readPoints(string pointsFileName);

    void morphTriangle(Mat &img1, Mat &img2, Mat &img, std::vector<Point2f> &t1, std::vector<Point2f> &t2, std::vector<Point2f> &t, double alpha);
    void applyAffineTransform(Mat &warpImage, Mat &src, std::vector<Point2f> &srcTri, std::vector<Point2f> &dstTri);
    void loadTriangleList();



};
