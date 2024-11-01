#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// <summary>
///  Detecting shapes and contours
/// </summary>
Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

void getContours(Mat imgDil,Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	for (int i = 0; i < contours.size(); i++) 
	{
		int area = contourArea(contours[i]);
		cout << area << endl;

		vector<vector<Point>>conPoly(contours.size());
		vector<Rect> boundRect(contours.size());
		string objectType;

		if (area > 1000) 
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			cout<<conPoly[i].size()<<endl;

			boundRect[i] = boundingRect(conPoly[i]);
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);*/
			int objCor = (int)conPoly[i].size();
			if (objCor == 3) { objectType = "Tri"; }
			if (objCor == 4) {

				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				cout << aspRatio << endl;
				if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "Square"; }
				else { objectType = "Rect"; }
			}
			if (objCor > 4) { objectType = "Circle"; }

			putText(img, objectType, {boundRect[i].x,boundRect[i].y - 5}, FONT_HERSHEY_DUPLEX, .6, Scalar(255, 0, 0), 1);

		};
	}

}

void main() {

	string path = "Resources/shapes.png";
	Mat img = imread(path);

	// Pre processing
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);

	// Finding Contours
	getContours(imgDil,img);

	imshow("Image", img);
	/*imshow("Image Gray", imgGray);
	imshow("Image Blur", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dialated", imgDil);*/
	waitKey(0);

}