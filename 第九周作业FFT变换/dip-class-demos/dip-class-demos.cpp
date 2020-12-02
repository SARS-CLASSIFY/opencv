// dip-class-demos.cpp : �������̨Ӧ�ó������ڵ㡣
//������и��ӡ�����
/****************************************************
brief:FFT�任�������ͬ�ߴ�ͼƬ�ֱ�ȡ��Ƶ���Ƶ�ź�
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
	//��ʼ��ʱ
	double start = static_cast<double>(cvGetTickCount());
	cv::Mat src = imread("max.jpg", 0);
	cv::Mat src1 = imread("egx.jpg", 0);
	cv::Mat dstmathigh,dstmatlow,dstimg;
	//dftDemo();
	//mouseROI();
	//selectPolygon1(src,dstmathigh);
	ifft_fselect(src, dstmathigh, 0);//ģʽ0��ѡȡ��Ƶ����ȥ����ѡƵ��
	mousePoints.swap(vector<Point>());
	ifft_fselect(src1, dstmatlow, 1);//ģʽ1��ѡȡ��Ƶ����ѡ����ѡƵ��
	//ifftDemo();
	//������ʱ
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//��ʾʱ��
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//ͼ�����
	addWeighted(dstmathigh,0.8,dstmatlow,0.2,0.0,dstimg);//�����ɵ�
	imshow("dstimg", dstimg);
	waitKey(0);
	//imshow("dstlow", dstmatlow);
	//imshow("dsthigh", dstmathigh);
	//�ȴ�������Ӧ�����������������
	//system("pause");
    return 0;
}

