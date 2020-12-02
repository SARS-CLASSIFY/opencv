// dip-class-demos.cpp : 定义控制台应用程序的入口点。
//鼠标点击有个坑。。。
/****************************************************
brief:FFT变换后对两张同尺寸图片分别取低频与高频信号
date:2020.12.2
author:SRS
****************************************************/
#include "stdafx.h"
#include <opencv.hpp>
#include "funtions.h"
#include "applicantion.h"
using namespace cv;
using namespace std;
extern std::vector<Point>  mousePoints;
int main()
{
	//开始计时
	double start = static_cast<double>(cvGetTickCount());
	cv::Mat src = imread("max.jpg", 0);
	cv::Mat src1 = imread("egx.jpg", 0);
	cv::Mat dstmathigh,dstmatlow,dstimg;
	//dftDemo();
	//mouseROI();
	//selectPolygon1(src,dstmathigh);
	ifft_fselect(src, dstmathigh, 0);//模式0，选取高频区域，去除所选频域
	mousePoints.swap(vector<Point>());
	ifft_fselect(src1, dstmatlow, 1);//模式1，选取低频区域，选择所选频域
	//ifftDemo();
	//结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//图像叠加
	addWeighted(dstmathigh,0.8,dstmatlow,0.2,0.0,dstimg);//参数可调
	imshow("dstimg", dstimg);
	waitKey(0);
	//imshow("dstlow", dstmatlow);
	//imshow("dsthigh", dstmathigh);
	//等待键盘响应，按任意键结束程序
	//system("pause");
    return 0;
}

