#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>
using namespace cv;
using namespace std;

void my_calcHOG(Mat refMat, float* ref_hist, int nAngle, int blockSize) {
	int nX = refMat.cols / blockSize;
	int nY = refMat.rows / blockSize;
	int cellSize = blockSize;
	//�������ؼ����ݶȺͷ���
	Mat gx, gy;
	Mat mag, angle;//mag�洢��ֵ��angle�洢�Ƕ�
	Sobel(refMat, gx, CV_32F, 1, 0, 1);
	Sobel(refMat, gy, CV_32F, 0, 1, 1);
	//XY�����ݶ�
	cartToPolar(gx, gy, mag, angle, true);


	//���㵥һ����ֱ��ͼ
	CvRect roi;//ѡȡ�ض�����
	roi.width = cellSize;
	roi.height = cellSize;


	int bins = 9 * nX * nY;//�Ƕ�����Ϊ8λ

	for (int i = 0;i < nY;i++) {
		for (int j = 0;j < nX;j++) {
			cv::Mat roiMat;
			cv::Mat roiMag;
			cv::Mat roiAgl;
			roi.x = cellSize * j;
			roi.y = cellSize * i;
			//��ֵͼ��
			roiMat = refMat(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);
			//��ǰcell��һ��Ԫ���������е�λ��
			int head = (i * nX + j) * nAngle;

			for (int n = 0;n < roiMat.rows;n++) {
				for (int m = 0;m < roiMat.cols;m++) {
					float agl_val = (roiAgl.at<float>(n, m) > 180) ? roiAgl.at<float>(n, m) - 180 : roiAgl.at<float>(n, m);//����0��180��
					float mag_val = (roiMag.at<float>(n, m));
					int hist_x = agl_val / 20;
					ref_hist[hist_x + head] += (agl_val - hist_x * 20.0) / 20.0 * mag_val;
					ref_hist[hist_x + 1 + head] += ((hist_x + 1.0) * 20 - agl_val) / 20.0 * mag_val;
				}
			}
		}
	}
}

