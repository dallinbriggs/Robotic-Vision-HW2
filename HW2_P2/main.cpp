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
    Mat image_color;
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
    fstream fileOutput;

    cameraMatrix = Mat::eye(3, 3, CV_64F);

    vector<vector<Point3f>> objectPoints(0);
    vector<vector<Point2f>> imagePoints;
    distCoeffs = Mat::zeros(8, 1, CV_64F);
    imagePoints.clear();
    int numCornersHor = 10;
    int numCornersVer = 7;
    int numSquares = numCornersHor * numCornersVer;

    vector<Point3f> obj;
    for(int j=0;j<numSquares;j++)
        obj.push_back(Point3f(j/numCornersHor, j%numCornersHor, 0.0f));

    header = "/home/dallin/Dropbox/Robotic_Vision/Calibration_Image_JPG/AR";
    tail = ".jpg";
    for(int i=1; i<41; i++)
    {
        filename = header + to_string(i) + tail;
        image = imread(filename,CV_LOAD_IMAGE_GRAYSCALE);
        image_color = imread(filename,CV_LOAD_IMAGE_COLOR);

        patternsize = cvSize(10,7);
        imageSize = cvSize(640,480);
        bool corners_detected = findChessboardCorners(image,patternsize,corners);
        if(corners_detected)
        {
            /// Set the neeed parameters to find the refined corners
            Size winSize = Size( 5, 5 );
            Size zeroZone = Size( -1, -1 );
            TermCriteria criteria = TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 );
            cornerSubPix(image,corners,winSize,zeroZone,criteria);
            imagePoints.push_back(corners);
//            objectPoints.resize(imagePoints.size(),objectPoints[0]);

            objectPoints.push_back(obj);

        }
        drawChessboardCorners(image_color,patternsize,corners,corners_detected);
        imshow("Briggs", image_color);
        waitKey(50);

//        objectPoints->push_back(corners);
    }


    calibrateCamera(objectPoints,imagePoints,image.size(),cameraMatrix,distCoeffs,rvecs,tvecs,0);
    cout << cameraMatrix << endl;
    cout << distCoeffs << endl;
    stringstream buffer;
    buffer << cameraMatrix << endl;
    buffer << distCoeffs;
    string fileOutName = "/home/dallin/robotic_vision/HW2/HW2_P2/Intrinsic_Parameters";
    fileOutput.open(fileOutName,fstream::out);
    fileOutput << buffer.str();
    fileOutput.close();


    waitKey(0);

    return 0;
}
