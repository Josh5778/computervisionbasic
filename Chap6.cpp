#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;
Mat imgHSV, mask;

int main() {
    // Stage 1: Load Image and Convert to HSV
    string path = "Resources/shapes.png";
    Mat img = imread(path);

    
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    namedWindow("Trackbars", (640, 200));
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);

    while (true) {
        // Stage 2: Apply `inRange` to Create Mask
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);

        // Display the images
        imshow("Image", img);
        imshow("Image HSV", imgHSV);
        imshow("Image Mask", mask);

        waitKey(1);
    }

    return 0;
}
