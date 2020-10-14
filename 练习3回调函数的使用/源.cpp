#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

string window_name = "binary mat";

void threshod_Mat(int th, void* data)
{
	Mat src = *(Mat*)(data);

	Mat dst;


	threshold(src, dst, th, 255, 0);
	imshow(window_name, dst);
}

int main()
{
	Mat srcImg;
	Mat grayImg;
	int lowth = 30;
	int maxth = 255;
	srcImg = imread("D:\\1.jpg");//ͼƬ����·���Զ�����

	if (!srcImg.data) {
		cout << "ͼ������ʧ��" << endl;
		return 0;
	}
	namedWindow(window_name, WINDOW_NORMAL);//��������
	cvtColor(srcImg, grayImg, CV_BGR2GRAY);
	imshow(window_name, grayImg);
	createTrackbar(
		"threshod_Mat",
		window_name,
		&lowth,
		maxth,
		threshod_Mat,
		&grayImg
	);
	waitKey(0);
	return 0;
}