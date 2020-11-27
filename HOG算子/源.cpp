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
	Mat src2 = imread("img2.jpg", 0);//����3��ͼƬ

	int blockSize = 16;
	int nAngle = 9;
	int nX = src.cols / blockSize;
	int nY = src.rows / blockSize;
	int bins = 9 * nX * nY;//�����ܵ�ֱ��ͼ������=810
	
	//float* ref_hist = new float[bins];
	//memset(ref_hist, 0, sizeof(float) * bins);
	float ref_hist[810] = {0};
	float ref_hist1[810] = { 0 };
	float ref_hist2[810] = { 0 };

	my_calcHOG(src,ref_hist,nAngle,blockSize);//�����Զ���HOG�����ϳɵ��ܵ�ֱ��ͼ����ref_hist��
	my_calcHOG(src1, ref_hist1, nAngle, blockSize);
	my_calcHOG(src2, ref_hist2, nAngle, blockSize);

	float dis1 = normL2Sqr(ref_hist,ref_hist1,bins);
	float dis2 = normL2Sqr(ref_hist, ref_hist2, bins);
	
	cout << dis1 << "  " << dis2 << endl;

	//ͼ�񻮷ֳ�CELL
	/**
	Mat refMat = src;

	int cellSize = 16;
	int nX = refMat.cols / cellSize;
	int nY = refMat.rows / cellSize;

	int nAngle = 9;

	//�������ؼ����ݶȺͷ���
	Mat gx, gy;
	Mat mag, angle;//mag�洢��ֵ��angle�洢�Ƕ�
	Sobel(grayimg, gx, CV_32F, 1, 0, 1);
	Sobel(grayimg, gy, CV_32F, 0, 1, 1);
	//XY�����ݶ�
	cartToPolar(gx, gy, mag, angle, true);

	//���㵥һ����ֱ��ͼ
	CvRect roi;//ѡȡ�ض�����
	roi.width = cellSize;
	roi.height = cellSize;

	//�����ڴ���
	int bins = 9*nX*nY;//�Ƕ�����Ϊ8λ

	float * ref_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float) * bins);

	//float ref_hist1[9*nX*nY] = { 0 };
	//��������ݶ�ֱ��ͼ
	for (int i = 0;i < nY;i++) {
		for (int j = 0;j < nX;j++) {
			cv::Mat roiMat;
			cv::Mat roiMag;
			cv::Mat roiAgl;
			roi.x = cellSize * j;
			roi.y = cellSize * i;
			//��ֵͼ��
			roiMat = grayimg(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);
			//��ǰcell��һ��Ԫ���������е�λ��
			int head = (i * nX + j) * nAngle;

			for (int n = 0;n < roiMat.rows;n++) {
				for (int m = 0;m < roiMat.cols;m++) {
					float agl_val = (roiAgl.at<float>(n, m) > 180) ? roiAgl.at<float>(n, m)-180 : roiAgl.at<float>(n, m);//����0��180��
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
