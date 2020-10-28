#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat frame;
	frame = imread("1.jpg");
	double scale = 0.5;
	double i_minH = 0;
	double i_maxH = 20;
	double i_minS = 43;
	double i_maxS = 255;
	double i_minV = 55;
	double i_maxV = 255;
	Mat hsvMat;
	Mat detectMat;
	cvtColor(frame, hsvMat, COLOR_BGR2HSV);

	cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);
	cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

	return 0;
}