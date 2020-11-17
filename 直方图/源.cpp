#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;


int main()
{
	VideoCapture capture(0);
	Mat myframe;
	Mat grayframe;
	Mat srcImage = imread("D:/1.jpg", 0);
	//视频捕获

	Mat dstHist;//输出目标直方图
	int dims = 1;
	float hranges[] = { 0,255 };
	const float* ranges[] = { hranges };//定义每一维的数值取值范围范围
	int size = 256;
	int channels = 0;//通道数

	int scale = 1;
	Mat dstImage(size * scale, size, CV_8U, Scalar(0));//作为输出直方图
	double minValue = 0;
	double maxValue = 0;


	while (1) {
		capture >> myframe; //获取当前帧
		cvtColor(myframe, grayframe, CV_BGR2GRAY);

			//计算直方图
		
		calcHist(&grayframe, 1, 0, Mat(), dstHist, dims, &size, ranges);
		
		minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
		
		//开始绘制直方图

		int hpt = saturate_cast<int>(0.9 * size);
		
		dstImage = 0;
		
		for (int i = 0;i < 256;i++) {
			float binvalue = dstHist.at<float>(i);
			int realvalue = saturate_cast<int>(binvalue * hpt / maxValue);
			//利用rectangle函数画图
			rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realvalue), Scalar(255));



		}
		

		
		namedWindow("test", WINDOW_NORMAL);
		imshow("video", myframe);
		imshow("test", dstImage);
		waitKey(20);

	}
	return 0;

}