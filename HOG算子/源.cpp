#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>
#include "my_calHOG.h"
using namespace cv;
using namespace std;


int main()
{
	Mat src = imread("hogTemplate.jpg",0);
	Mat src1 = imread("img1.jpg",0);
	Mat src2 = imread("img2.jpg", 0);//读入3张图片

	int blockSize = 16;
	int nAngle = 9;
	int nX = src.cols / blockSize;
	int nY = src.rows / blockSize;
	int bins = 9 * nX * nY;//计算总的直方图横轴数=810
	
	//float* ref_hist = new float[bins];
	//memset(ref_hist, 0, sizeof(float) * bins);
	float ref_hist[810] = {0};
	float ref_hist1[810] = { 0 };
	float ref_hist2[810] = { 0 };

	my_calcHOG(src,ref_hist,nAngle,blockSize);//调用自定义HOG函数合成的总的直方图存于ref_hist中
	my_calcHOG(src1, ref_hist1, nAngle, blockSize);
	my_calcHOG(src2, ref_hist2, nAngle, blockSize);

	float dis1 = normL2Sqr(ref_hist,ref_hist1,bins);
	float dis2 = normL2Sqr(ref_hist, ref_hist2, bins);
	
	cout << dis1 << "  " << dis2 << endl;

	//图像划分成CELL
	/**
	Mat refMat = src;

	int cellSize = 16;
	int nX = refMat.cols / cellSize;
	int nY = refMat.rows / cellSize;

	int nAngle = 9;

	//所有像素计算梯度和方向
	Mat gx, gy;
	Mat mag, angle;//mag存储赋值，angle存储角度
	Sobel(grayimg, gx, CV_32F, 1, 0, 1);
	Sobel(grayimg, gy, CV_32F, 0, 1, 1);
	//XY方向梯度
	cartToPolar(gx, gy, mag, angle, true);

	//计算单一区域直方图
	CvRect roi;//选取特定区域
	roi.width = cellSize;
	roi.height = cellSize;

	//开辟内存区
	int bins = 9*nX*nY;//角度量化为8位

	float * ref_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float) * bins);

	//float ref_hist1[9*nX*nY] = { 0 };
	//历遍计算梯度直方图
	for (int i = 0;i < nY;i++) {
		for (int j = 0;j < nX;j++) {
			cv::Mat roiMat;
			cv::Mat roiMag;
			cv::Mat roiAgl;
			roi.x = cellSize * j;
			roi.y = cellSize * i;
			//赋值图像
			roiMat = grayimg(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);
			//当前cell第一个元素在数组中的位置
			int head = (i * nX + j) * nAngle;

			for (int n = 0;n < roiMat.rows;n++) {
				for (int m = 0;m < roiMat.cols;m++) {
					float agl_val = (roiAgl.at<float>(n, m) > 180) ? roiAgl.at<float>(n, m)-180 : roiAgl.at<float>(n, m);//采用0到180度
					float mag_val = (roiMag.at<float>(n, m));
					int hist_x = agl_val/20;
					ref_hist[hist_x+head] +=  (agl_val - hist_x * 20.0) / 20.0 * mag_val;
					ref_hist[hist_x + 1+head] += ((hist_x + 1.0) * 20 - agl_val) / 20.0 * mag_val;
					delete[] ref_hist;
				}
			}

			delete[] ref_hist;

		}
	}
	*/


	waitKey(0);
	return 0;

}
