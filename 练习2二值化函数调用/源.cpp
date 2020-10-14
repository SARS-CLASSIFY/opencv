#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	VideoCapture cap(0);

	double scale = 0.5;

	while (1)
	{
		Mat frame;
		Mat grayframe;
		Mat result;//自适应阈值结果
		Mat result_OTSU;//大津法结果

		cap >> frame;
		Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);
		Mat rFrame = Mat(ResImgSiz, frame.rows * scale);
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);//差值算法

		cvtColor(rFrame, grayframe, CV_BGR2GRAY);

		
		threshold(grayframe,result_OTSU,100, 255, THRESH_OTSU);
		adaptiveThreshold(grayframe,result,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,31,10);//自适应阈值算法

		imshow("whie: in the range", result);
		imshow("frame", rFrame);
		imshow("OTSUFRAME", result_OTSU);
		waitKey(30);
	}



}