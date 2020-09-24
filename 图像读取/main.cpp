#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "dark.h"

using namespace cv;
int main()
{

	Mat image = imread("D:\\1.JPG");

	Mat edge, grayimage;
	cvtColor(image, grayimage, CV_BGR2GRAY);//转化为2灰度值
	blur(grayimage, edge, Size(3, 3));//降噪处理

	Canny(edge, edge, 3, 9, 3);
	namedWindow("test", WINDOW_NORMAL);
	imshow("test", edge);
	waitKey(0);


	//等待用户按键
	waitKey(0);
	return 0;
}