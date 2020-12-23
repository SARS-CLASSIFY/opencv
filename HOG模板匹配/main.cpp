#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>
#include "funtions.h"
using namespace cv;
using namespace std;


/**********************手动实现，通过 HOG (Histogram-of-Oriented-Gradients)比较图像相似度*************************/
int compareImages(cv:: Mat refMat,cv:: Mat plMat,cv:: Mat bgMat)
{

	/**
	//读入图像
	cv::Mat refMat = imread("../testImages\\hogTemplate.jpg", 0);
	cv::Mat plMat = imread("../testImages\\img1.jpg", 0);
	cv::Mat bgMat = imread("../testImages\\img2.jpg", 0);

	if (refMat.empty() || plMat.empty() || bgMat.empty()) {
		std::cout << "failed to read image!:" << std::endl;
		return -1;
	}
	*/

	//参数设置
	int nAngle = 8;
	int blockSize = 16;
	int nX = refMat.cols / blockSize;
	int nY = refMat.rows / blockSize;

	int bins = nX * nY * nAngle;


	float* ref_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float) * bins);
	float* pl_hist = new float[bins];
	memset(pl_hist, 0, sizeof(float) * bins);
	float* bg_hist = new float[bins];
	memset(bg_hist, 0, sizeof(float) * bins);

	int reCode = 0;
	//计算三张输入图片的HOG
	reCode = calcHOG(refMat, ref_hist, nAngle, blockSize);
	reCode = calcHOG(plMat, pl_hist, nAngle, blockSize);
	reCode = calcHOG(bgMat, bg_hist, nAngle, blockSize);

	if (reCode != 0) {
		return -1;
	}

	//计算直方图距离
	float dis1 = normL2(ref_hist, pl_hist, bins);
	float dis2 = normL2(ref_hist, bg_hist, bins);

	std::cout << "distance between reference and img1:" << dis1 << std::endl;
	std::cout << "distance between reference and img2:" << dis2 << std::endl;

	(dis1 <= dis2) ? (std::cout << "img1 is similar" << std::endl) : (std::cout << "img2 is similar" << std::endl);


	imshow("ref", refMat);
	imshow("img1", plMat);
	imshow("img2", bgMat);

	waitKey(0);

	delete[] ref_hist;
	delete[] pl_hist;
	delete[] bg_hist;
	destroyAllWindows();

	return 0;
}


int main()
{

	cv::Mat refMat = imread("1.jpg", 0);
	cv::Mat plMat = imread("2.jpg", 0);
	cv::Mat bgMat = imread("3.jpg", 0);

	if (refMat.empty() || plMat.empty() || bgMat.empty()) {
		std::cout << "failed to read image!:" << std::endl;
		return -1;
	}
	compareImages(refMat, plMat, bgMat);
	return 0;




}