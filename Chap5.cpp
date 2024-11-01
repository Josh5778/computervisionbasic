#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/// <summary>
///  Warp Images
/// </summary>

float w = 250, h = 350;
Mat matrixk,matrixQ,matrixJ,matrix9, imgWarpk, imgWarpQ,imgWarpJ,imgWarp9;

void main() {

	string path = "Resources/cards.jpg";
	Mat img = imread(path);

	Point2f srck[4] = { {529,142},{771,190},{405,395},{674,457} };
	Point2f srcQ[4] = { {63,325},{335,280},{92,630},{402,571} };
	Point2f srcJ[4] = { {776,108},{1016,84},{844,358},{1115,330} };
	Point2f src9[4] = { {740,386},{1022,438},{644,704},{964,782} };
	Point2f dst[4] = { {0.0f,0.0f},{w,0},{0.0f,h},{w,h} };

	matrixk = getPerspectiveTransform(srck, dst);
	warpPerspective(img, imgWarpk, matrixk, Point(w, h));
	matrixQ = getPerspectiveTransform(srcQ, dst);
	warpPerspective(img, imgWarpQ, matrixQ, Point(w, h));
	matrixJ = getPerspectiveTransform(srcJ, dst);
	warpPerspective(img, imgWarpJ, matrixJ, Point(w, h));
	matrix9 = getPerspectiveTransform(src9, dst);
	warpPerspective(img, imgWarp9, matrix9, Point(w, h));


	for (int i = 0; i < 4; i++) 
	{
		circle(img, srck[i],10, Scalar(0, 0, 255), 2);
	}
	for (int i = 0; i < 4; i++)
	{
		circle(img, srcQ[i], 10, Scalar(0, 0, 255), 2);
	}
	for (int i = 0; i < 4; i++)
	{
		circle(img, srcJ[i], 10, Scalar(0, 0, 255), 2);
	}
	for (int i = 0; i < 4; i++)
	{
		circle(img, src9[i], 10, Scalar(0, 0, 255), 2);
	}

	imshow("Image", img);
	imshow("Image Warp King", imgWarpk);
	imshow("Image Warp Queen", imgWarpQ);
	imshow("Image Warp Jack", imgWarpJ);
	imshow("Image Warp 9", imgWarp9);
	waitKey(0);

}



