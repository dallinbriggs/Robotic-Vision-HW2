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
    Mat current_frame;
    Mat previous_frame;
    Mat frame_thresh;
    Mat motion;
    Mat first_frame;
    string filename;
    string header;
    string tail;

    VideoWriter VOut; // Create a video write object.
    // Initialize video write object (only done once). Change frame size to match your camera resolution.
    VOut.open("VideoOut.avi", CV_FOURCC('M', 'P', 'E', 'G') , 30, Size(640, 480), 1);

    namedWindow("Dallin Briggs",1);
    //    SimpleBlobDetector blobby;

    // Setup SimpleBlobDetector parameters.
    SimpleBlobDetector::Params params;

    // Change thresholds
    params.minThreshold = 10;
    params.maxThreshold = 255;

    // Filter by Area.
    params.filterByArea = true;
    params.minArea = 100;

    // Filter by Circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.1;

    // Filter by Convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.87;

    // Filter by Inertia
    params.filterByInertia = true;
    params.minInertiaRatio = .3;

#if CV_MAJOR_VERSION < 3   // If you are using OpenCV 2

    // Set up detector with params
    SimpleBlobDetector detector(params);

    // You can use the detector this way
    // detector.detect( im, keypoints);

#else

    // Set up detector with params
    Ptr<SimpleBlobDetector> blobby = SimpleBlobDetector::create(params);

    // SimpleBlobDetector::create creates a smart pointer.
    // So you need to use arrow ( ->) instead of dot ( . )
    // detector->detect( im, keypoints);

#endif


    for(int i = 5; i < 41; i++)
    {
        header = "/home/dallin/Dropbox/Robotic_Vision/HW1_P3/Baseball_images/1R";
        tail = ".jpg";
        filename = header + to_string(i) + tail;

        first_frame = imread(header + '5' + tail, CV_LOAD_IMAGE_GRAYSCALE);
        image = imread(filename,CV_LOAD_IMAGE_GRAYSCALE);

        current_frame.copyTo(previous_frame);

        current_frame = image;
        if(previous_frame.empty())
        {
            previous_frame = Mat::zeros(current_frame.size(), current_frame.type()); // prev frame as black
            //signed 16bit mat to receive signed difference
        }
        absdiff(current_frame, first_frame, motion);
        GaussianBlur(motion,motion, Size(7,7), 1.5, 1.5);
        threshold(motion, frame_thresh,10,255,1);


        // Detect blobs.
        std::vector<KeyPoint> keypoints;
        blobby->detect(frame_thresh, keypoints);

        // Draw detected blobs as red circles.
        // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
        Mat im_with_keypoints;
        drawKeypoints(current_frame, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

        cout << keypoints.size() << endl;
        // Show blobs
        imshow("keypoints", im_with_keypoints );
        VOut << im_with_keypoints;
        //        imshow("Briggs", frame_circles);

        waitKey(100);

    }

    return 0;
}
