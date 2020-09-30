#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "mycalhist.h"
using namespace cv;
using namespace std;
/**
	*brief -- RGB��ͨ��ֱ��ͼ�Ļ���
	* 09/30/2020
	*SRS
 */
int main()
{
	int scale = 1;
	int size = 256;
	Mat srcImage = imread("1.jpg");//����ԭʼͼ
	float R[256] = { 0 }, G[256] = { 0 }, B[256] = { 0 };
	mycalchist(srcImage, R, G, B);//����ֱ��ͼ�����ú���)

	Mat dstImage_R(size * scale, size, CV_8U, Scalar(0));//��ΪRͨ��Ŀ�����ֱ��ͼ
	Mat dstImage_G(size * scale, size, CV_8U, Scalar(0));//��ΪGͨ��Ŀ�����ֱ��ͼ
	Mat dstImage_B(size * scale, size, CV_8U, Scalar(0));//��ΪBͨ��Ŀ�����ֱ��ͼ

	float R_maxvalue = 0, G_maxvalue = 0, B_maxvalue = 0;	//	Ѱ�����ֵ����ֱ��ͼ����ʾ
	for (int n = 0;n < 256;n++) {
		if (R_maxvalue < R[n])
			R_maxvalue = R[n];
		if (G_maxvalue < G[n])
			G_maxvalue = G[n];
		if (B_maxvalue < B[n])
			B_maxvalue = B[n];
	}

	int hpt = 0.9*size;
	for (int i = 0;i < 256;i++) {

		float R_binvalue = R[i];//����Rͨ����ͼ�Ĳ���
		int R_realvalue =saturate_cast<int>(R_binvalue * hpt/R_maxvalue );
		float G_binvalue = G[i];//����Gͨ����ͼ�Ĳ���
		int G_realvalue = saturate_cast<int>(G_binvalue * hpt / G_maxvalue);
		float B_binvalue = B[i];//����Bͨ����ͼ�Ĳ���
		int B_realvalue = saturate_cast<int>(B_binvalue * hpt / B_maxvalue);
		//����rectange��ͼ
		rectangle(dstImage_R, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - R_realvalue), Scalar(255));
		rectangle(dstImage_G, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - G_realvalue), Scalar(255));
		rectangle(dstImage_B, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - B_realvalue), Scalar(255));

	}
	imshow("R_dstimage", dstImage_R);
	imshow("G_dstimage", dstImage_G);
	imshow("B_dstimage", dstImage_B);
	waitKey(0);

}