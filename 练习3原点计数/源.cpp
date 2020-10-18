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
	morphologyEx(binaryimg, outimg,MORPH_CLOSE, element);//执行闭运算
	outimg = ~outimg;//图像取反
	/*****连通域部分******/
	int commontnum;
	Mat labels, stats, centroids;
	commontnum = connectedComponentsWithStats(outimg, labels, stats, centroids, 8, CV_32S);

	/*****显示部分*******/
	namedWindow("结果图", WINDOW_NORMAL);
	imshow("结果图", outimg);
	cout << "原点数目为：" << commontnum - 1 << endl;
	waitKey(0);
	return 0;


}