#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	int i, j;
	Mat srcimg = imread("2.jpg");
	Mat grayimg, binaryimg;
	cvtColor(srcimg, grayimg, CV_BGR2GRAY);
	threshold(grayimg, binaryimg, 90, 255, THRESH_OTSU);
	Mat outimg;
	Mat element = getStructuringElement(MORPH_RECT, Size(21, 21));
	morphologyEx(binaryimg, outimg,MORPH_CLOSE, element);//ִ�б�����
	outimg = ~outimg;//ͼ��ȡ��
	/*****��ͨ�򲿷�******/
	int commontnum;
	Mat labels, stats, centroids;
	commontnum = connectedComponentsWithStats(outimg, labels, stats, centroids, 8, CV_32S);

	/*****��ʾ����*******/
	namedWindow("���ͼ", WINDOW_NORMAL);
	imshow("���ͼ", outimg);
	cout << "ԭ����ĿΪ��" << commontnum - 1 << endl;
	waitKey(0);
	return 0;


}