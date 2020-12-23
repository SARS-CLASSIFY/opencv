#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>
#include "funtions.h"
using namespace cv;
using namespace std;


/**********************�ֶ�ʵ�֣�ͨ�� HOG (Histogram-of-Oriented-Gradients)�Ƚ�ͼ�����ƶ�*************************/
/**brief: HOG���ƶȱȽϺ���
  *input:  refMat plMat ģ��ͼƬ�Լ���ƥ��ͼƬ
  *output: ֱ��ͼ��ֵ
***/
float compareImages(cv:: Mat refMat,cv:: Mat plMat)
{

	/**
	//����ͼ��
	cv::Mat refMat = imread("../testImages\\hogTemplate.jpg", 0);
	cv::Mat plMat = imread("../testImages\\img1.jpg", 0);
	cv::Mat bgMat = imread("../testImages\\img2.jpg", 0);

	if (refMat.empty() || plMat.empty() || bgMat.empty()) {
		std::cout << "failed to read image!:" << std::endl;
		return -1;
	}
	*/
	//��������
	int nAngle = 8;
	int blockSize = 16;
	int nX = refMat.cols / blockSize;
	int nY = refMat.rows / blockSize;

	int bins = nX * nY * nAngle;


	float* ref_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float) * bins);
	float* pl_hist = new float[bins];
	memset(pl_hist, 0, sizeof(float) * bins);
	/*float* bg_hist = new float[bins];
	memset(bg_hist, 0, sizeof(float) * bins);*/

	int reCode = 0;
	//������������ͼƬ��HOG
	reCode = calcHOG(refMat, ref_hist, nAngle, blockSize);
	reCode = calcHOG(plMat, pl_hist, nAngle, blockSize);
	//reCode = calcHOG(bgMat, bg_hist, nAngle, blockSize);

	if (reCode != 0) {
		return -1;
	}

	//����ֱ��ͼ����
	float dis1 = normL2(ref_hist, pl_hist, bins);
	return dis1;//����ֱ��ͼ�ľ���
	
	//float dis2 = normL2(ref_hist, bg_hist, bins);

	//std::cout << "distance between reference and img1:" << dis1 << std::endl;
	//std::cout << "distance between reference and img2:" << dis2 << std::endl;

	//(dis1 <= dis2) ? (std::cout << "img1 is similar" << std::endl) : (std::cout << "img2 is similar" << std::endl);


	//imshow("ref", refMat);
	//imshow("img1", plMat);
	//imshow("img2", bgMat);

	waitKey(0);

	delete[] ref_hist;
	delete[] pl_hist;
	//delete[] bg_hist;
	destroyAllWindows();

	return 0;
}


int main()
{

	cv::Mat refMat = imread("hog.jpg", 0);

	Mat tempMat;



	if (refMat.empty()) {
		std::cout << "failed to read image!:" << std::endl;
		return -1;
	}

	//��ȡģ��
	Rect2d r;
	r = selectROI(refMat, true);
	tempMat = refMat(r);//�õ�ģ��
	destroyAllWindows;


	int widthref = refMat.cols;
	int highref = refMat.rows;
	int width = tempMat.cols;
	int high = tempMat.rows;
	int count = 0;
	Point2d target;
	float distancemin = 1000000,distance;
	Mat ROI,ROI1;//��������
	for (int i = 0;i < widthref - width+1;i++) {
		for (int j = 0;j < highref - high+1 ;j++) {
			Rect rect(i, j,width, high);
			refMat(rect).copyTo(ROI);//�õ�����ͼ��
			count++;
			
			distance = compareImages(ROI, tempMat);
			
			if (distance <= distancemin) {
				distancemin = distance;
				target.x = i;
				target.y = j;
			}
			
		}
	}


	Rect ta(target.x, target.y, width, high);
	cv::rectangle(refMat,ta, cv::Scalar(0, 0, 255), 1,1, 0);

	imshow("result", refMat);
	waitKey(0);
	return 0;

}