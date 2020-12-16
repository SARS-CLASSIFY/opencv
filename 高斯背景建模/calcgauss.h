#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <math.h>
using namespace cv;
using namespace std;
//高斯背景建模函数->求每个点的均值和方差
int calcGaussianBackground(std::vector<cv::Mat> srcMats, cv::Mat meanMat, cv::Mat varMat) {
	int rows = srcMats[0].rows;
	int cols = srcMats[0].cols;



	for (int high = 0;high < rows;high++) {//历遍目标矩阵（矩阵由图像构成）
		for (int width = 0;width < cols;width++) {

			int sum = 0;
			float var = 0;

			for (int i = 0;i < srcMats.size(); i++) {
				sum += srcMats[i].at<uchar>(high, width);
			}
			meanMat.at<uchar>(high, width) = sum / srcMats.size();//计算均值

			for (int i = 0;i < srcMats.size();i++) {
				var += pow(srcMats[i].at<uchar>(high, width) - meanMat.at<uchar>(high, width), 2);
			}
			varMat.at<float>(high,width) = var/srcMats.size();//计算方差
		}
	}

	return 0;
}

//高斯背景差分函数
int gaussThreshold(cv::Mat srcMat,cv::Mat meanMat,cv::Mat varMat,float weight,cv::Mat& dstMat) {
	int srcI;
	int dstI;
	int meanI;
	int rows = srcMat.rows;
	int cols = srcMat.cols;
	for (int high = 0;high < rows;high++) {
		for (int width = 0;width < cols;width++) {
			srcI = srcMat.at<uchar>(high, width);
			meanI = meanMat.at<uchar>(high, width);
			int dif = abs(srcI - meanI);
			int th = weight * varMat.at<float>(high,width);

			if (dif >= th) {
				dstMat.at<uchar>(high, width) = 255;
			}
			else {
				dstMat.at<uchar>(high, width) = 0;
			}

		}
	}
	return 0;
}