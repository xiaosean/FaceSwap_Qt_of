#include "faceswap.h"
using namespace std;
faceswap::faceswap(){    
    faceTracker1.setup();
    faceTracker2.setup();
//    if(triVec.size() == 0)
    loadTriangleList();    //empty average image
}
void faceswap::setIminateLandmarks(Mat iminateModel){
    faceTracker1.update(iminateModel);
    std::vector<ofxFaceTracker2Instance> faceTracker1_faces = faceTracker1.getInstances();
    if(faceTracker1_faces.size() > 0){
        ofxFaceTracker2Landmarks faceLm_2 = faceTracker1_faces.at(0).getLandmarks();
        dest_points = faceLm_2.getCvImagePoints();
        std::cout << "dest_points" << dest_points.size() << std::endl;
    }
}
Mat faceswap::swap(Mat src){
    img1 = src;
    faceTracker1.update(img1);
    return(convexSwap(src));
}
Mat faceswap::swap(Mat src, Mat iminateModel){
    img1 = src;
    faceTracker1.update(img1);
    if(dest_points.size() == 0){
        img2 = iminateModel;
        faceTracker2.update(img2);
        return(convexSwap(src, iminateModel));
    }else{
        return(convexSwap(src));
    }
}
Mat faceswap::convexSwap(Mat src){

    img1.convertTo(img1, CV_32F);
    Mat imgMorph = img1;
    Mat srcM = cv::Mat::zeros(img1.size(), CV_8UC1);

    std::vector<ofxFaceTracker2Instance> faceTracker1_faces = faceTracker1.getInstances();
    if(faceTracker1_faces.size() == 0)
        return imgMorph/255;
    ofxFaceTracker2Landmarks faceLm_1 = faceTracker1_faces.at(0).getLandmarks();
    std::vector<cv::Point2f> src_points = faceLm_1.getCvImagePoints();
    std::vector<int> v;
    int x,y,z;

    for(int i = 0; i < triVec.size(); ++i){
         v = triVec.at(i);
         x = v.at(0);
         y = v.at(1);
         z = v.at(2);
        // Triangles
        std::vector<Point2f> srcTri, dstTri;
        // Triangle corners for image 2.
        srcTri.push_back( dest_points[x] );
        srcTri.push_back( dest_points[y] );
        srcTri.push_back( dest_points[z] );
        // Triangle corners for image 1.
        dstTri.push_back( src_points[x] );
        dstTri.push_back( src_points[y] );
        dstTri.push_back( src_points[z] );
        std::vector<cv::Point> points;
        points.push_back(Point( src_points[x].x, src_points[x].y));
        points.push_back(Point(src_points[y].x, src_points[y].y));
        points.push_back(Point(src_points[z].x, src_points[z].y));
        cv::Mat warp_mat = cv::getAffineTransform(srcTri, dstTri);
        cv::warpAffine(img2, srcM, warp_mat, srcM.size());
        cv::Mat mask = cv::Mat::zeros(imgMorph.size(), CV_8U);
        cv::fillConvexPoly(mask, points, cvScalar(255));
        srcM.copyTo(imgMorph, mask);
    }
    return imgMorph/255.0;


}
Mat faceswap::convexSwap(Mat src, Mat swapModel){

    img1.convertTo(img1, CV_32F);
    img2.convertTo(img2, CV_32F);
    Mat imgMorph = img1;
    Mat srcM = cv::Mat::zeros(img1.size(), CV_8UC1);

    std::vector<ofxFaceTracker2Instance> faceTracker1_faces = faceTracker1.getInstances();
    if(faceTracker1_faces.size() == 0)
        return imgMorph/255;
    ofxFaceTracker2Landmarks faceLm_1 = faceTracker1_faces.at(0).getLandmarks();
    std::vector<cv::Point2f> src_points = faceLm_1.getCvImagePoints();
    std::vector<ofxFaceTracker2Instance> faceTracker2_faces = faceTracker2.getInstances();
    if(faceTracker2_faces.size() == 0)
        return imgMorph/255;
    ofxFaceTracker2Landmarks faceLm_2 = faceTracker2_faces.at(0).getLandmarks();
    dest_points = faceLm_2.getCvImagePoints();
    std::vector<int> v;
    int x,y,z;

    for(int i = 0; i < triVec.size(); ++i){
         v = triVec.at(i);
         x = v.at(0);
         y = v.at(1);
         z = v.at(2);
        // Triangles
        std::vector<Point2f> srcTri, dstTri;
        // Triangle corners for image 2.
        srcTri.push_back( dest_points[x] );
        srcTri.push_back( dest_points[y] );
        srcTri.push_back( dest_points[z] );
        // Triangle corners for image 1.
        dstTri.push_back( src_points[x] );
        dstTri.push_back( src_points[y] );
        dstTri.push_back( src_points[z] );
        std::vector<cv::Point> points;
        points.push_back(Point( src_points[x].x, src_points[x].y));
        points.push_back(Point(src_points[y].x, src_points[y].y));
        points.push_back(Point(src_points[z].x, src_points[z].y));
        cv::Mat warp_mat = cv::getAffineTransform(srcTri, dstTri);
        cv::warpAffine(img2, srcM, warp_mat, srcM.size());
        cv::Mat mask = cv::Mat::zeros(imgMorph.size(), CV_8U);
        cv::fillConvexPoly(mask, points, cvScalar(255));
        srcM.copyTo(imgMorph, mask);
    }
    return imgMorph/255.0;
}
Mat faceswap::morphSwap(ofxFaceTracker2& faceTracker1, ofxFaceTracker2& faceTracker2, Mat src, Mat swapModel){
   faceTracker1.setup();
   faceTracker2.setup();
    //alpha controls the degree of morph
    double alpha = 0.5;
    //convert Mat to float data type
    img1 = src;
    img2 = swapModel;

    img1.convertTo(img1, CV_32F);
    img2.convertTo(img2, CV_32F);
    img2.resize(img1.rows, img1.cols);

    //empty average image
     Mat imgMorph;
//     img1.convertTo(imgMorph, CV_32FC3);
     imgMorph = img1.clone();
//     imshow("Morphed temp Face", imgMorph/255);
//     waitKey(0);
//     destroyAllWindows();

//    Mat imgMorph = Mat::zeros(img1.size(), CV_32FC3);
//    Mat imgMorph = img1.clone();
    //Read points
    // vector<Point2f> src_points = readPoints( filename1 + ".txt");
    // vector<Point2f> dest_points = readPoints( filename2 + ".txt");
//    faceTracker1.update(img1);
//    faceTracker1.update(img1);
    std::vector<ofxFaceTracker2Instance> faceTracker1_faces = faceTracker1.getInstances();
    ofxFaceTracker2Landmarks faceLm_1 = faceTracker1_faces.at(0).getLandmarks();
    std::vector<cv::Point2f> src_points = faceLm_1.getCvImagePoints();
 // vector<Point2f> dest_points = readPoints( filename2 + ".txt");
//    faceTracker2.update(img2);
    std::vector<ofxFaceTracker2Instance> faceTracker2_faces = faceTracker2.getInstances();
    ofxFaceTracker2Landmarks faceLm_2 = faceTracker2_faces.at(0).getLandmarks();
    std::vector<cv::Point2f> dest_points = faceLm_2.getCvImagePoints();
    std::vector<Point2f> out_points;

    //compute weighted average point coordinates
    for(int i = 0; i < src_points.size(); i++)
    {
        float x, y;
        x = (1 - alpha) * src_points[i].x + alpha * dest_points[i].x;
        y =  ( 1 - alpha ) * src_points[i].y + alpha * dest_points[i].y;
//        x = dest_points[i].x;
//        y =  dest_points[i].y;
        out_points.push_back(Point2f(x,y));

    }


    // //Read triangle indices
    // ifstream ifs("/home/spark/Desktop/learnopencv/FaceMorph/tri.txt");
    // int x,y,z;

    // while(ifs >> x >> y >> z)
    // {
    if(triVec.size() == 0)
        loadTriangleList();    //empty average image

    std::vector<int> v;
    int x,y,z;
    for(int i = 0; i < triVec.size(); ++i){
         v = triVec.at(i);
         x = v.at(0);
         y = v.at(1);
         z = v.at(2);
        // Triangles
        std::vector<Point2f> t1, t2, t;

        // Triangle corners for image 1.
        t1.push_back( src_points[x] );
        t1.push_back( src_points[y] );
        t1.push_back( src_points[z] );

        // Triangle corners for image 2.
        t2.push_back( dest_points[x] );
        t2.push_back( dest_points[y] );
        t2.push_back( dest_points[z] );

        // Triangle corners for morphed image.
        t.push_back( out_points[x] );
        t.push_back( out_points[y] );
        t.push_back( out_points[z] );
        morphTriangle(img1, img2, imgMorph, t1, t2, t, alpha);
    }
//    imgMorph.convertTo(imgMorph, CV_8U);
//    // Display Result
//    imgMorph.convertTo(imgMorph, CV_32F);
    Mat bgrImgMorph;
    cvtColor( imgMorph,bgrImgMorph, CV_RGB2BGR);

    imshow("Morphed Face", bgrImgMorph/255);
    waitKey(0);
    destroyAllWindows();

    return imgMorph/255.0;


}
void faceswap::loadTriangleList(){
    //Read triangle indices
    ifstream ifs("/home/spark/Desktop/learnopencv/FaceMorph/tri.txt");
    int x,y,z;
    int upperBound = 68;
    std::vector<int> v(3, 0);
     while(ifs >> x >> y >> z)
    {
         if(x < upperBound && y < upperBound && z < upperBound){
            v.at(0) = x;
            v.at(1) = y;
            v.at(2) = z;
            triVec.push_back(v);
        }
    }


}
// Apply affine transform calculated using srcTri and dstTri to src
void faceswap::applyAffineTransform(Mat &warpImage, Mat &src, std::vector<Point2f> &srcTri, std::vector<Point2f> &dstTri)
{

    // Given a pair of triangles, find the affine transform.
    Mat warpMat = getAffineTransform( srcTri, dstTri );

    // Apply the Affine Transform just found to the src image
    warpAffine( src, warpImage, warpMat, warpImage.size(), INTER_LINEAR, BORDER_REFLECT_101);
}

// Warps and alpha blends triangular regions from img1 and img2 to img
void faceswap::morphTriangle(Mat &img1, Mat &img2, Mat &img, std::vector<Point2f> &t1, std::vector<Point2f> &t2, std::vector<Point2f> &t, double alpha)
{

    // Find bounding rectangle for each triangle
    Rect r = boundingRect(t);
    Rect r1 = boundingRect(t1);
    Rect r2 = boundingRect(t2);

    // Offset points by left top corner of the respective rectangles
    std::vector<Point2f> t1Rect, t2Rect, tRect;
    std::vector<Point> tRectInt;
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

// Read points stored in the text files
std::vector<Point2f> faceswap::readPoints(string pointsFileName)
{
    std::vector<Point2f> points;
    ifstream ifs(pointsFileName);
    float x, y;
    while(ifs >> x >> y)
    {
        points.push_back(Point2f(x,y));
    }

    return points;
}

faceswap::~faceswap(){
    faceTracker1.stop();
    faceTracker2.stop();
}
