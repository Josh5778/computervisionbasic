#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// <summary>
///  Importing images
/// </summary>

//void main() {
//
//	string path = "Resources/test.png";
//	Mat img = imread(path);
//	imshow("Image", img);
//	waitKey(0);
//
//}

/// <summary>
///  Importing videos
/// </summary>

//void main() {
//
//	string path = "Resources/test_video.mp4";
//	VideoCapture cap(path);
//	Mat img;
//
//	while (true) {
//		
//		cap.read(img);
//		imshow("Image", img);
//		waitKey(1);
//	}
//}



/// <summary>
///  Webcam
/// </summary>

void main() {

	VideoCapture cap(0);
	Mat img;

	while (true) {
		cap.read(img);
		imshow("Image", img);
		waitKey(1);
	}
}