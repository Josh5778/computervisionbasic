#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>
	
using namespace std;
using namespace cv;

//int main() {
//	string path = "keanu_reeves.jpg";
//	Mat img = imread(path);
//	imshow("Frame", img);
//	waitKey(0);
//
//}

int main() {
	try {
		/*VideoCapture video(0);
		Mat img;*/

		CascadeClassifier facedetect;
		string path = "Resources/test.png";
		Mat img = imread(path);
		facedetect.load("haarcascade_frontalface_default.xml");

		//video.read(img);

		vector<Rect> faces;

		facedetect.detectMultiScale(img, faces, 1.3, 5);

		cout << faces.size() << endl;

		for (int i = 0; i < faces.size(); i++) {
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(50, 50, 255), 3);
			putText(img, to_string(faces.size()), Point(10, 40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 1);
		} 

		imshow("Frame", img);
		waitKey(1);
	}
	catch (const cv::Exception& e) {
		std::cerr << "OpenCV error: " << e.what() << std::endl;
	}
}

