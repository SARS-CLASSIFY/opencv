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

	int nBG = 200; //��ȡ�����ڽ�ģ��֡��
	float wVar = 1.0;//����Ȩ�أ����ڶ�ֵ��
	int cnt = 0;//��¼��ǰ֡��
	cv::Mat frame;
	cv::Mat meanMat;
	cv::Mat dstMat;
	cv::Mat varMat;

	std::vector<cv::Mat> srcMats;//���ڼ��㱳����ģ��ͼ��
	while (1) {
		capVideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);//ת��Ϊ�Ҷ�ͼ��
		if (cnt < nBG) {		//����ǰ��N֡�������и�˹��ģ
			srcMats.push_back(frame);
		}
		else if (cnt == nBG) {
			meanMat.create(frame.size(), CV_8UC1);
			varMat.create(frame.size(), CV_32FC1);

			std::cout << "start calculate gaussBG!" << endl;
			calcGaussianBackground(srcMats, meanMat, varMat);
		}

		else {//�������
			dstMat.create(frame.size(), CV_8UC1);
			gaussThreshold(frame, meanMat, varMat,wVar, dstMat);//���и�˹�������
			imshow("result", dstMat);
			imshow("src", frame);
			waitKey(30);


		}
		cnt++;

	}

	return  0;

}