#include "funtions.h"
#include <math.h>

using namespace cv;
using namespace std;

//�ֶ�ʵ�� HOG (Histogram-of-Oriented-Gradients) 
int calcHOG(cv::Mat src, float* hist, int nAngle, int cellSize)
{

	if (cellSize > src.cols || cellSize > src.rows) {
		return -1;
	}

	//��������
	int nX = src.cols / cellSize;
	int nY = src.rows / cellSize;

	int binAngle = 360 / nAngle;

	//�����ݶȼ��Ƕ�
	Mat gx, gy;
	Mat mag, angle;
	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	// x�����ݶȣ�y�����ݶȣ��ݶȣ��Ƕȣ������������or�Ƕ�
	// Ĭ���ǻ���radians��ͨ�����һ����������ѡ��Ƕ�degrees.

	/************************************************
	cartToPolar���� ����ģ�ͣ�
	cartToPolar(InputArray x, InputArray y,
							  OutputArray magnitude, OutputArray angle,
							  bool angleInDegrees = false);


	�������ܣ�
	. InputArray x/InputArray y�������ݶ�x/y
	.  OutputArray magnitude�������ֵ
	. OutputArray angle������Ƕ�

	**************************************************/
	cartToPolar(gx, gy, mag, angle, true);

	cv::Rect roi;
	roi.x = 0;
	roi.y = 0;
	roi.width = cellSize;
	roi.height = cellSize;

	for (int i = 0; i < nY; i++) {
		for (int j = 0; j < nX; j++) {

			cv::Mat roiMat;
			cv::Mat roiMag;
			cv::Mat roiAgl;

			roi.x = j * cellSize;
			roi.y = i * cellSize;

			//��ֵͼ��
			roiMat = src(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);

			//��ǰcell��һ��Ԫ���������е�λ��
			int head = (i * nX + j) * nAngle;

			for (int n = 0; n < roiMat.rows; n++) {
				for (int m = 0; m < roiMat.cols; m++) {
					//����Ƕ����ĸ�bin��ͨ��int�Զ�ȡ��ʵ��
					int pos = (int)(roiAgl.at<float>(n, m) / binAngle);
					//�����ص��ֵΪȨ��
					hist[head + pos] += roiMag.at<float>(n, m);
				}
			}

		}
	}

	return 0;
}

float normL2(float* Hist1, float* Hist2, int size)
{
	float sum = 0;
	for (int i = 0; i < size; i++) {
		sum += (Hist1[i] - Hist2[i]) * (Hist1[i] - Hist2[i]);
	}
	sum = sqrt(sum);
	return sum;
}
