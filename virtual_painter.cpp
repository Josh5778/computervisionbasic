#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// <summary>
///  Project 1 - virtual painter
/// </summary>

//<hmin, smin, vmin, hmax, smax, vmax>
Mat img;
vector<vector<int>> newPoints;
vector<vector<int>> myColours{ {164,167,87,179,255,255} // Red
								,{63,80,0,129,184,255} }; // Blue

vector<Scalar> myColourValues{ {0,0,255} // Red
								,{255,0,0} }; // Blue


Point getContours(Mat imgDil) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>>conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	//drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
	Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;
		string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			
			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;


			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);


		};
	}
	return myPoint;
}

vector<vector<int>> findcolour(Mat img)
{
	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	for (int i = 0; i < myColours.size(); i++)
	{
		Scalar lower(myColours[i][0], myColours[i][1], myColours[i][2]);
		Scalar upper(myColours[i][3], myColours[i][4], myColours[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		//imshow(to_string(i), mask);
		Point myPoint = getContours(mask);

		if (myPoint.x != 0 && myPoint.y != 0) {
			newPoints.push_back({ myPoint.x,myPoint.y,i });
		}
	}
	return newPoints;
}

void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColourValues)
{

	for (int i = 0; i < newPoints.size();i++)
	{
		circle(img, Point(newPoints[i][0],newPoints[i][1]), 10, myColourValues[newPoints[i][2]], FILLED);
	}
}
void main() {

	VideoCapture cap(0);

	while (true) {
		cap.read(img);
		newPoints = findcolour(img);
		drawOnCanvas(newPoints,myColourValues);

		imshow("Image", img);
		waitKey(1);
	}
}