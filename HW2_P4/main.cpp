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
    Mat distCoeffs;
    Mat rvec;
    Mat tvec;
    Mat cameraMatrix;
    FileStorage fs("/home/dallin/robotic_vision/HW2/HW2_P4/Intrinsic_calibration.xml", FileStorage::READ);
    fs["CameraMatrix"] >> cameraMatrix;
    fs["DistortionCoefficients"] >> distCoeffs;

    Mat ImagePoints;
    Mat ObjectPoints;
    FileStorage fs2("/home/dallin/robotic_vision/HW2/HW2_P4/DataPoints.xml", FileStorage::READ);
    fs2["ImagePoints"] >> ImagePoints;
    fs2["ObjectPoints"] >> ObjectPoints;

    bool PNP_solved = solvePnP(ObjectPoints,ImagePoints,cameraMatrix,distCoeffs,rvec, tvec,false,SOLVEPNP_ITERATIVE);
    Rodrigues(rvec,rvec,noArray());
    if(PNP_solved)
    {
        cout << rvec << endl << tvec << endl;
    }
    else
    {
        cout << "Error in solving PNP" << endl;
        return -1;
    }

    FileStorage fs3("Extrinsic_calibration.xml", FileStorage::WRITE);
    fs3 << "RotationMatrix" << rvec;
    fs3 << "TranslationVector" << tvec;
//    image = imread("/home/dallin/robotic_vision/HW2/HW2_P4/Object_with_Corners.jpg",CV_LOAD_IMAGE_GRAYSCALE);
//    undistort(image,image_undistort,cameraMatrix,distCoeffs,noArray());
//    absdiff(image_undistort,image,image_diff);
//    imshow("Briggs",image_diff);

    waitKey(0);

    return 0;
}
