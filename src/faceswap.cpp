#include "faceswap.h"
using namespace std;
faceswap::faceswap(){
}
Mat faceswap::swap(ofxFaceTracker2& faceTracker1, ofxFaceTracker2& faceTracker2, Mat src, Mat swapModel){
    std::cout<<"debug setep in faceswap3" << std::endl;
    // string filename1 = "/home/spark/Desktop/learnopencv/FaceMorph/hillary_clinton.jpg";
    // string filename2 ="/home/spark/Desktop/learnopencv/FaceMorph/ted_cruz.jpg";
    int mode = 1;
    if(mode == 0){
        return(morphSwap(faceTracker1, faceTracker2, src, swapModel));
    }
    else{
        return(convexSwap(faceTracker1, faceTracker2, src, swapModel));
    }

}
Mat faceswap::convexSwap(ofxFaceTracker2& faceTracker1, ofxFaceTracker2& faceTracker2, Mat src, Mat swapModel){
   faceTracker1.setup();
   faceTracker2.setup();

    //convert Mat to float data type
    img1 = src;
    img2 = swapModel;
    std::cout << "img1 col = " << img1.cols << std::endl;
    std::cout << "img2 col = "<< img2.cols << std::endl;

    img1.convertTo(img1, CV_32F);
    img2.convertTo(img2, CV_32F);
    img2.resize(img1.rows, img1.cols);
//    // Display Result
//    imshow("img1 Face", img1 / 255.0);
//    waitKey(0);
//    // Display Result
    std::cout<< img1.cols << std::endl;

    std::cout<<"debug setep in faceswap3..." << std::endl;
    std::cout<< img2.cols << std::endl;
//    imshow("img2 Face", img2/255);
//    waitKey(0);
//    destroyAllWindows();

    //empty average image
     Mat imgMorph = cv::Mat::zeros(img1.size(), CV_8UC1);
     Mat srcM = cv::Mat::zeros(img1.size(), CV_8UC1);

//     img1.convertTo(imgMorph, CV_32FC3);
     // imgMorph = img1.clone();
//     imshow("Morphed temp Face", imgMorph/255);
//     waitKey(0);
//     destroyAllWindows();

//    Mat imgMorph = Mat::zeros(img1.size(), CV_32FC3);
//    Mat imgMorph = img1.clone();
    std::cout<<"debug setep in faceswap3.1" << std::endl;
    //Read points
    // vector<Point2f> src_points = readPoints( filename1 + ".txt");
    // vector<Point2f> dest_points = readPoints( filename2 + ".txt");
//    faceTracker1.update(img1);
//    faceTracker1.update(img1);
    std::vector<ofxFaceTracker2Instance> faceTracker1_faces = faceTracker1.getInstances();
    ofxFaceTracker2Landmarks faceLm_1 = faceTracker1_faces.at(0).getLandmarks();
    std::vector<cv::Point2f> src_points = faceLm_1.getCvImagePoints();
    std::cout<<"debug setep in faceswap3.2" << std::endl;
 // vector<Point2f> dest_points = readPoints( filename2 + ".txt");
//    faceTracker2.update(img2);
    std::vector<ofxFaceTracker2Instance> faceTracker2_faces = faceTracker2.getInstances();
    ofxFaceTracker2Landmarks faceLm_2 = faceTracker2_faces.at(0).getLandmarks();
    std::vector<cv::Point2f> dest_points = faceLm_2.getCvImagePoints();
    std::cout<<"debug setep in faceswap3.3" << std::endl;

    if(triVec.size() == 0)
        loadTriangleList();    //empty average image
    std::vector<cv::Point> src_points2d;
    for(int i = 0; i < src_points.size(); ++i){
        src_points2d.push_back(Point( src_points[i].x, src_points[i].y));
    }
    std::vector<int> v;
    int x,y,z;
    std::cout<< "triVec size() = "<< triVec.size() << std::endl;
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
//        points.push_back(Point( dest_points[x].x, dest_points[x].y));
//        points.push_back(Point(dest_points[y].x, dest_points[y].y));
//        points.push_back(Point(dest_points[z].x, dest_points[z].y));
        cv::Mat warp_mat = cv::getAffineTransform(srcTri, dstTri);
//        cout << "finish warp mat" << std::endl;
        cv::warpAffine(img2, srcM, warp_mat, srcM.size());
//        cout << "finish warpAffine" << std::endl;
//        cv::Rect rect = cv::boundingRect(src_points);
//        cout << "finish rect" << std::endl;
        cv::Mat mask = cv::Mat::zeros(imgMorph.size(), CV_8U);
//        cout << "finish mask" << points.size()<<std::endl;
        cv::fillConvexPoly(mask, points, cvScalar(255));
//        cout << "finish fillConvexPoly" << std::endl;
        srcM.copyTo(imgMorph, mask);

    }

//    cv::Mat mask = cv::Mat::zeros(img1.size(), CV_8U);
//    cout << "src_points2d size = " << src_points2d.size() << endl;
//    cv::fillConvexPoly(mask, src_points2d, cvScalar(255));
//    cout << "mask size = " << mask.cols << "   " << mask.rows << endl;
//    Mat imgMorph2 = img1;
//    cout << "imgMorph2 = img1" << imgMorph2.cols << imgMorph2.rows << endl;
//    imgMorph.copyTo(imgMorph2, mask);
//    cout << "copy to imgMorph2" << imgMorph2.cols << imgMorph2.rows << endl;
//    imshow("Morphed Face", imgMorph2);
    Mat bgrImgMorph;
    cvtColor(imgMorph, bgrImgMorph, CV_RGB2BGR);
    cout << "cbgrImgMorph" << bgrImgMorph.cols << bgrImgMorph.rows << endl;

    imshow("Morphed Face", bgrImgMorph/255);

    waitKey(0);
//    destroyAllWindows();
    std::cout<<"return imgMorph;" << std::endl;
    return imgMorph/255.0;
//    Mat bgrImgMorph;
//    cvtColor(imgMorph, bgrImgMorph, CV_RGB2BGR);
//    imshow("Morphed Face", bgrImgMorph/255);
//    waitKey(0);
////    destroyAllWindows();
//    std::cout<<"return imgMorph;" << std::endl;
//    return imgMorph/255.0;


}
Mat faceswap::morphSwap(ofxFaceTracker2& faceTracker1, ofxFaceTracker2& faceTracker2, Mat src, Mat swapModel){
   faceTracker1.setup();
   faceTracker2.setup();
    //alpha controls the degree of morph
    double alpha = 0.5;
    //convert Mat to float data type
    img1 = src;
    img2 = swapModel;
    std::cout << "img1 col = " << img1.cols << std::endl;
    std::cout << "img2 col = "<< img2.cols << std::endl;

    img1.convertTo(img1, CV_32F);
    img2.convertTo(img2, CV_32F);
    img2.resize(img1.rows, img1.cols);
//    // Display Result
//    imshow("img1 Face", img1 / 255.0);
//    waitKey(0);
//    // Display Result
    std::cout<< img1.cols << std::endl;

    std::cout<<"debug setep in faceswap3..." << std::endl;
    std::cout<< img2.cols << std::endl;
//    imshow("img2 Face", img2/255);
//    waitKey(0);
//    destroyAllWindows();

    //empty average image
     Mat imgMorph;
//     img1.convertTo(imgMorph, CV_32FC3);
     imgMorph = img1.clone();
//     imshow("Morphed temp Face", imgMorph/255);
//     waitKey(0);
//     destroyAllWindows();

//    Mat imgMorph = Mat::zeros(img1.size(), CV_32FC3);
//    Mat imgMorph = img1.clone();
    std::cout<<"debug setep in faceswap3.1" << std::endl;
    //Read points
    // vector<Point2f> src_points = readPoints( filename1 + ".txt");
    // vector<Point2f> dest_points = readPoints( filename2 + ".txt");
//    faceTracker1.update(img1);
//    faceTracker1.update(img1);
    std::vector<ofxFaceTracker2Instance> faceTracker1_faces = faceTracker1.getInstances();
    ofxFaceTracker2Landmarks faceLm_1 = faceTracker1_faces.at(0).getLandmarks();
    std::vector<cv::Point2f> src_points = faceLm_1.getCvImagePoints();
    std::cout<<"debug setep in faceswap3.2" << std::endl;
 // vector<Point2f> dest_points = readPoints( filename2 + ".txt");
//    faceTracker2.update(img2);
    std::vector<ofxFaceTracker2Instance> faceTracker2_faces = faceTracker2.getInstances();
    ofxFaceTracker2Landmarks faceLm_2 = faceTracker2_faces.at(0).getLandmarks();
    std::vector<cv::Point2f> dest_points = faceLm_2.getCvImagePoints();
    std::cout<<"debug setep in faceswap3.3" << std::endl;

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
    std::cout<< "triVec size() = "<< triVec.size() << std::endl;
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

    std::cout<<"return imgMorph;" << std::endl;

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




//Mat faceswap::swap(Mat src, Mat swapModel){

//    std::cout<<"debug setep in faceswap3" << std::endl;
//    cv::Size size = swapModel.size();
//    faceTracker2.update(swapModel);
//    std::cout<<"debug setep in faceswap3.1" << std::endl;
//    std::vector<ofxFaceTracker2Instance> faceTracker2_faces = faceTracker2.getInstances();
//    std::cout<<"debug setep in faceswap1.1" << std::endl;

//    ofxFaceTracker2Landmarks faceLm_2 = faceTracker2_faces.at(0).getLandmarks();
//    EXpoints = faceLm_2.getCvImagePoints();
//    std::cout<<"debug setep in faceswap1" << std::endl;

//    std::vector<cv::Point> points;
//    for(int i = 0; i < faceLm_2.getCvImagePoints().size(); ++i){
//        points.push_back(cv::Point((EXpoints.at(i).x, EXpoints.at(i).y)));
//    }
//    std::cout<<"debug setep in faceswap1" << std::endl;

//    cv::Rect rect(0, 0, size.width, size.height);
//    cv::Subdiv2D subdiv(rect);
//    subdiv.insert(EXpoints);
//    std::vector<TRIANGLE_DESC> triList;
//    std::vector<cv::Vec6f> temp_result;
//    subdiv.getTriangleList(temp_result);
//    for (const auto _tmp_vec : temp_result)
//    {
//        cv::Point pt1((int)_tmp_vec[0], (int)_tmp_vec[1]);
//        cv::Point pt2((int)_tmp_vec[2], (int)_tmp_vec[3]);
//        cv::Point pt3((int)_tmp_vec[4], (int)_tmp_vec[5]);
//        long p1=99, p2=99, p3=99;
//        for (int i = 0; i < points.size(); i++)
//        {
//            if (pt1 == points.at(i)) {
//                p1 = i;
//            }else if (pt2 == points.at(i)) {
//                p2 = i;
//            }else if (pt3 == points.at(i)) {
//                p3 = i;
//            }
//        }
//        if (p1 == 99 || p2 == 99 || p3 == 99) continue;
//        triList.push_back(TRIANGLE_DESC(p1, p2, p3));
//    }
//    std::cout<<"debug setep in faceswap2" << std::endl;
//    cv::Mat im = img1;
//    cv::Mat im_small, im_display;
//    cv::Mat srcM = cv::Mat::zeros(im.size(), CV_8UC1);

//    // Resize image for face detection
//    cv::resize(im, im_small, cv::Size(), 1.0/FACE_DOWNSAMPLE_RATIO, 1.0/FACE_DOWNSAMPLE_RATIO);

//    // Change to dlib's image format. No memory is copied.
//    cv_image<bgr_pixel> cimg_small(im_small);
//    cv_image<bgr_pixel> cimg(im);

//    faceTracker1.update(img1);

//    std::vector<ofxFaceTracker2Instance> faceTracker1_faces = faceTracker1.getInstances();
//    ofxFaceTracker2Landmarks faceLm_1 = faceTracker1_faces.at(0).getLandmarks();
//    std::vector<cv::Point2f> srcPoints = faceLm_1.getCvImagePoints();
//    std::cout<<"debug setep in faceswap4" << std::endl;

    // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
    // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
    // long as temp is valid.  Also don't do anything to temp that would cause it
    // to reallocate the memory which stores the image as that will make cimg
    // contain dangling pointers.  This basically means you shouldn't modify temp
    // while using cimg.
    //cv_image<bgr_pixel> cimg(temp);

    // Detect faces
    //std::vector<rectangle> faces = detector(cimg);

//    if ( count % SKIP_FRAMES == 0 )
//    {
//        faces = detector(cimg_small);
//    }
    // Find the pose of each face.
//    std::vector<full_object_detection> shapes;

//    for (int i = 0; i < triList.size(); i++)
//    {
//        cv::Point2f srcTri[3];
//        srcTri[0] = cv::Point2f(EXpoints.at(triList.at(i).pt1).x, EXpoints.at(triList.at(i).pt1).y);
//        srcTri[1] = cv::Point2f(EXpoints.at(triList.at(i).pt2).x, EXpoints.at(triList.at(i).pt2).y);
//        srcTri[2] = cv::Point2f(EXpoints.at(triList.at(i).pt3).x, EXpoints.at(triList.at(i).pt3).y);



//        cv::Point2f dstTri[3];
//        dstTri[0] = cv::Point2f(srcPoints.at(triList.at(i).pt1).x, srcPoints.at(triList.at(i).pt1).y);
//        dstTri[1] = cv::Point2f(srcPoints.at(triList.at(i).pt2).x, srcPoints.at(triList.at(i).pt2).y);
//        dstTri[2] = cv::Point2f(srcPoints.at(triList.at(i).pt3).x, srcPoints.at(triList.at(i).pt3).y);

//        std::vector<cv::Point> points;
//        points.push_back(cv::Point(srcPoints.at(triList.at(i).pt1).x, srcPoints.at(triList.at(i).pt1).y));
//        points.push_back(cv::Point(srcPoints.at(triList.at(i).pt2).x, srcPoints.at(triList.at(i).pt2).y));
//        points.push_back(cv::Point(srcPoints.at(triList.at(i).pt3).x, srcPoints.at(triList.at(i).pt3).y));
//        cv::Mat warp_mat = cv::getAffineTransform(srcTri, dstTri);
//        cv::warpAffine(src, srcM, warp_mat, srcM.size());
//        cv::Rect rect = cv::boundingRect(points);
//        cv::Mat mask = cv::Mat::zeros(im.size(), CV_8U);
//        cv::fillConvexPoly(mask, points, cvScalar(255));
//        srcM.copyTo(im, mask);
//    }
//    std::cout<<"debug setep in faceswap5" << std::endl;

//    return im;

//    shapes.push_back(shape);

//    cv_image<bgr_pixel> cimgs(im);
//    // Display it all on the screen
//    win.clear_overlay();
//    win.set_image(cimgs);
//    win.add_overlay(render_face_detections(shapes));
//}


//Mat faceswap::swap(Mat src){
//    std::cout<<"debug setep in faceswap3" << std::endl;

//    //Speedup
//    _count ++;
//    _count = _count % 10000;
//    cv::Mat im(img1);

//    cv::Mat im_small(src), im_display;
//    cv::Mat srcM = cv::Mat::zeros(im.size(), CV_8UC1);
//    std::cout<<"debug setep in faceswap3.1" << std::endl;

//    // Resize image for face detection
//    cv::resize(im, im_small, cv::Size());
//    std::cout<<"debug setep in faceswap3.2" << std::endl;

//    // Change to dlib's image format. No memory is copied.
//    cv_image<bgr_pixel> cimg_small(im_small);
//    cv_image<bgr_pixel> cimg(im);
//    std::cout<<"debug setep in faceswap3.3" << std::endl;

//    faceTracker1.update(img1);
//    std::cout<<"debug setep in faceswap3.4" << std::endl;


//    std::vector<ofxFaceTracker2Instance> faceTracker1_faces = faceTracker1.getInstances();
//    ofxFaceTracker2Landmarks faceLm_1 = faceTracker1_faces.at(0).getLandmarks();
//    std::vector<cv::Point2f> srcPoints = faceLm_1.getCvImagePoints();
//    std::cout<<"debug setep in faceswap4" << std::endl;

//    // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
//    // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
//    // long as temp is valid.  Also don't do anything to temp that would cause it
//    // to reallocate the memory which stores the image as that will make cimg
//    // contain dangling pointers.  This basically means you shouldn't modify temp
//    // while using cimg.
//    //cv_image<bgr_pixel> cimg(temp);

//    // Detect faces
//    //std::vector<rectangle> faces = detector(cimg);

//    if ( count % SKIP_FRAMES == 0 )
//    {
//        faces = detector(cimg_small);
//    }
//    // Find the pose of each face.
//    std::vector<full_object_detection> shapes;

//    for (int i = 0; i < triList.size(); i++)
//    {
//        cv::Point2f srcTri[3];
//        srcTri[0] = cv::Point2f(EXpoints.at(triList.at(i).pt1).x, EXpoints.at(triList.at(i).pt1).y);
//        srcTri[1] = cv::Point2f(EXpoints.at(triList.at(i).pt2).x, EXpoints.at(triList.at(i).pt2).y);
//        srcTri[2] = cv::Point2f(EXpoints.at(triList.at(i).pt3).x, EXpoints.at(triList.at(i).pt3).y);



//        cv::Point2f dstTri[3];
//        dstTri[0] = cv::Point2f(srcPoints.at(triList.at(i).pt1).x, srcPoints.at(triList.at(i).pt1).y);
//        dstTri[1] = cv::Point2f(srcPoints.at(triList.at(i).pt2).x, srcPoints.at(triList.at(i).pt2).y);
//        dstTri[2] = cv::Point2f(srcPoints.at(triList.at(i).pt3).x, srcPoints.at(triList.at(i).pt3).y);

//        std::vector<cv::Point> points;
//        points.push_back(cv::Point(srcPoints.at(triList.at(i).pt1).x, srcPoints.at(triList.at(i).pt1).y));
//        points.push_back(cv::Point(srcPoints.at(triList.at(i).pt2).x, srcPoints.at(triList.at(i).pt2).y));
//        points.push_back(cv::Point(srcPoints.at(triList.at(i).pt3).x, srcPoints.at(triList.at(i).pt3).y));
//        cv::Mat warp_mat = cv::getAffineTransform(srcTri, dstTri);
//        cv::warpAffine(src, srcM, warp_mat, srcM.size());
//        cv::Rect rect = cv::boundingRect(points);
//        cv::Mat mask = cv::Mat::zeros(im.size(), CV_8U);
//        cv::fillConvexPoly(mask, points, cvScalar(255));
//        srcM.copyTo(im, mask);
//    }
//    std::cout<<"debug setep in faceswap5" << std::endl;
//    cout<< "in fs face1 vec size = "<< faceTracker1_faces.size() << std::endl;
//    cout<< "in fs face2 vec size = "<< faceTracker2_faces.size() << std::endl;
//    return im;

//    shapes.push_back(shape);

//    cv_image<bgr_pixel> cimgs(im);
//    // Display it all on the screen
//    win.clear_overlay();
//    win.set_image(cimgs);
//    win.add_overlay(render_face_detections(shapes));
//}


faceswap::~faceswap(){
    faceTracker1.stop();
    faceTracker2.stop();
}
