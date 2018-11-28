#include <opencv.hpp>
#include <opencv2\objdetect.hpp>
#include <opencv2\video.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

void detectAndDraw(Mat &img, CascadeClassifier &cascade, double scale);

int main(){
	string cascadeName = "F:/AllofGraduation/graduation project/classifer/Project1/Project1/cascade.xml";
	string videoName = "F:/AllofGraduation/videoTrafficData/TESTVIDIODATA/ImageSet/highway.avi";
	VideoCapture capture;
	if (!capture.open(videoName))
	{
		cerr << "ERROR: Could not load video file:" << videoName << endl;
		waitKey(0);
		return 0;
	}
	CascadeClassifier cascade;
	if (!cascade.load(cascadeName))
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		waitKey(0);
		return 0;
	}
	while (1)
	{
		Mat img;
		capture >> img;
		if (img.empty())
		{
			cerr << "ERROR: No Frame grab." << endl;
			break;
		}
		resize(img, img, Size(1.2*img.cols, 1.2*img.rows));
		detectAndDraw(img, cascade, 1);
		waitKey(30);
	}
	capture.release();
	waitKey(0);
	return 0;
}

void detectAndDraw(Mat &img, CascadeClassifier &cascade, double scale)
{
	int i = 0;
	double t = 0;
	vector<Rect> targets;
	Scalar color(0, 0, 255);
	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);
	equalizeHist(gray, gray);
	cascade.detectMultiScale(gray, targets,1.1,16, CASCADE_DO_CANNY_PRUNING,Size(24,24));
	for (int i = 0; i < targets.size(); i++)
	{
		rectangle(img, targets[i], color);
	}
	imshow("Results", img);
}