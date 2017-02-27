#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include <fstream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat image;
    Mat image_undistort;
    Mat image_diff;
    vector<Point2f> corners;
    Size patternsize;
    string filename;
    string header;
    string tail;
    Size imageSize;
    Mat distCoeffs;
    vector<Mat> rvecs;
    vector<Mat> tvecs;
    Mat cameraMatrix;
    FileStorage fs("/home/dallin/robotic_vision/HW3/HW3_P3/Intrinsic_calibration_baseball_left.xml", FileStorage::READ);
    fs["CameraMatrix"] >> cameraMatrix;
    fs["DistortionCoefficients"] >> distCoeffs;

    image = imread("/home/dallin/robotic_vision/HW3/Images/stereoL1.bmp",CV_LOAD_IMAGE_GRAYSCALE);
    undistort(image,image_undistort,cameraMatrix,distCoeffs,noArray());
    absdiff(image_undistort,image,image_diff);
    imshow("Briggs",image_diff);

//    imwrite("Turned_diff.jpg",image_diff);

    waitKey(0);

    return 0;
}
