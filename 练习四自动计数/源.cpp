#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	int i;
	Mat srcimg = imread("1.jpg");
	Mat grayimg, binaryimg;
	cvtColor(srcimg, grayimg, CV_BGR2GRAY);
	threshold(grayimg,binaryimg,100,255,THRESH_OTSU);
	binaryimg = ~binaryimg;
	/*******���п�������ȥ��С��*******/
	Mat output;
	Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
	morphologyEx(binaryimg,output, MORPH_OPEN, element);
	/*******��ͨ�򲿷�****************/
	int commontnum;
	Mat labels, stats, centroids;
	commontnum = connectedComponentsWithStats(output, labels, stats, centroids, 8, CV_32S);
	int truenum = 0;//ʵ�ʵ�������Ŀ
	/*************************����ѡ��************************************
	**********��ȡstats��ֵ������ͨ���height>=250���ж�Ϊ�ǻ�����*******/
	for (i = 0;i < commontnum;i++) {
		if (stats.at<int>(i, 3) <= 250) {
			truenum++;
		}
	}


	cout <<"��������Ϊ��"<< truenum << endl;
	//cout << stats << endl;//��ӡ���������ֵ��������ѡ�����

	namedWindow("out", WINDOW_NORMAL);
	imshow("out", output);
	waitKey(0);
	return 0;

}