#include "faceswap.h"
using namespace std;
faceswap::faceswap(){    
    faceTracker1.setup();
    faceTracker2.setup();
    loadTriangleList();    //empty average image
}
Mat faceswap::swap(Mat src, Mat iminateModel){
    img1 = src;
    faceTracker1.update(img1);
    // if it can get imitate Face Landmarks then return original image
    if(dest_points.size() == 0 && !setIminateLandmarks(iminateModel))
        return img1/255;
    //swap face and alpha blending
    return(convexSwap(src));

}
Mat faceswap::convexSwap(Mat src){
    img1.convertTo(img1, CV_32F);
    Mat faceSrc = cv::Mat::zeros(img1.size(), CV_32F);
    Mat faceDest = cv::Mat::zeros(img1.size(), CV_32F);
    Mat srcM = cv::Mat::zeros(img1.size(), CV_32F);
//    Mat oriM = cv::Mat::zeros(img1.size(), CV_32F);
    std::vector<ofxFaceTracker2Instance> faceTracker1_faces = faceTracker1.getInstances();
    if(faceTracker1_faces.size() == 0)
        if(lastMorph.rows > 0)
            return lastMorph/255;
        else
            return faceSrc/255;
    ofxFaceTracker2Landmarks faceLm_1 = faceTracker1_faces.at(0).getLandmarks();
    src_points = faceLm_1.getCvImagePoints();
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
        std::vector<cv::Point> tri_points;
        tri_points.push_back(Point( src_points[x].x, src_points[x].y));
        tri_points.push_back(Point(src_points[y].x, src_points[y].y));
        tri_points.push_back(Point(src_points[z].x, src_points[z].y));
        cv::Mat destWarpMat = cv::getAffineTransform(srcTri, dstTri);
//        cv::Mat srcWarpMat = cv::getAffineTransform(srcTri, srcTri);
        cv::warpAffine(img2, srcM, destWarpMat, srcM.size());
//        cv::warpAffine(img1, oriM, srcWarpMat, oriM.size());
        cv::Mat mask = cv::Mat::zeros(faceSrc.size(), CV_8U);
        cv::fillConvexPoly(mask, tri_points, cvScalar(255));
       // copy imitate face to my face
        srcM.copyTo(faceSrc, mask);
        // save imitate face for alpha blending
        img1.copyTo(faceDest, mask);
    }
//    Mat imgMorph = lastMorph = faceSrc;
    // alpha blending to transform color
    Mat imgMorph = alphaBlending(0.4, img1, faceSrc, faceDest);
    lastMorph = imgMorph;
    return imgMorph/255;
}
Mat faceswap::alphaBlending(double alpha, Mat faceBase, Mat faceSrc, Mat faceDest){
    Mat faceBlending = cv::Mat::zeros(img1.size(), CV_32F);
//    double alpha = .4f;
    double beta = ( 1.0 - alpha );
    addWeighted( faceSrc, alpha, faceDest, beta, 0, faceBlending);
    cv::Mat mask = cv::Mat::zeros(faceBase.size(), CV_8U);
    std::vector<Point> points2D;
    // set a convexpoly becuase it has orderly characteristic.
    for(int i = 0; i < 17; ++i){
         points2D.push_back(Point(src_points[i].x, src_points[i].y));
    }
    for(int i = 27-1; i > 16; --i){
         points2D.push_back(Point(src_points[i].x, src_points[i].y));
    }
    cv::fillConvexPoly(mask, points2D, cvScalar(255));
    faceBlending.copyTo(faceBase, mask);
    return faceBase;
}
//
bool faceswap::setIminateLandmarks(Mat iminateModel){
    faceTracker2.update(iminateModel);
    img2 = iminateModel;
    std::vector<ofxFaceTracker2Instance> faceTracker2_faces = faceTracker2.getInstances();
    if(faceTracker2_faces.size() == 0)
        return false;
    ofxFaceTracker2Landmarks faceLm_2 = faceTracker2_faces.at(0).getLandmarks();
    dest_points = faceLm_2.getCvImagePoints();
    img2.convertTo(img2, CV_32F);
    return true;
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
