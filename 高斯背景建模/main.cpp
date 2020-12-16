#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include "calcgauss.h"
using namespace cv;
using namespace std;

int main()
{
	VideoCapture capVideo(0);
	if (!capVideo.isOpened()) {
		std::cout << "camera open failed!" << endl;
		return -1;
	}

	int nBG = 200; //读取的用于建模的帧数
	float wVar = 1.0;//方差权重，用于二值化
	int cnt = 0;//记录当前帧数
	cv::Mat frame;
	cv::Mat meanMat;
	cv::Mat dstMat;
	cv::Mat varMat;

	std::vector<cv::Mat> srcMats;//用于计算背景建模的图像
	while (1) {
		capVideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);//转化为灰度图像
		if (cnt < nBG) {		//利用前面N帧背景进行高斯建模
			srcMats.push_back(frame);
		}
		else if (cnt == nBG) {
			meanMat.create(frame.size(), CV_8UC1);
			varMat.create(frame.size(), CV_32FC1);

			std::cout << "start calculate gaussBG!" << endl;
			calcGaussianBackground(srcMats, meanMat, varMat);
		}

		else {//背景差分
			dstMat.create(frame.size(), CV_8UC1);
			gaussThreshold(frame, meanMat, varMat,wVar, dstMat);//进行高斯背景差分
			imshow("result", dstMat);
			imshow("src", frame);
			waitKey(30);


		}
		cnt++;

	}

	return  0;

}