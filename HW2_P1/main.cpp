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
    int channels;
    Mat corners;
    Size patternsize;
    string filename;

    filename = "/home/dallin/Dropbox/Robotic_Vision/Calibration_Image_JPG/AR1.jpg";
    image = imread(filename,CV_LOAD_IMAGE_GRAYSCALE);
    image_color = imread(filename,CV_LOAD_IMAGE_COLOR);

    channels = image.channels();
    patternsize = cvSize(10,7);
    bool corners_detected = findChessboardCorners(image,patternsize,corners);

    if(corners_detected)
    {
        /// Set the neeed parameters to find the refined corners
        Size winSize = Size( 5, 5 );
        Size zeroZone = Size( -1, -1 );
        TermCriteria criteria = TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 );
        cornerSubPix(image,corners,winSize,zeroZone,criteria);
    }

    drawChessboardCorners(image_color,patternsize,corners,corners_detected);
    imshow("Briggs", image_color);
    imwrite("chessboard_circles.jpg", image_color);

    waitKey(0);

    return 0;
}
