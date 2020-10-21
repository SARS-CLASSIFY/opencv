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
	/*******进行开运算来去除小点*******/
	Mat output;
	Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
	morphologyEx(binaryimg,output, MORPH_OPEN, element);
	/*******连通域部分****************/
	int commontnum;
	Mat labels, stats, centroids;
	commontnum = connectedComponentsWithStats(output, labels, stats, centroids, 8, CV_32S);
	int truenum = 0;//实际的器件数目
	/*************************特征选择************************************
	**********读取stats的值，若连通域的height>=250则判断为非回形针*******/
	for (i = 0;i < commontnum;i++) {
		if (stats.at<int>(i, 3) <= 250) {
			truenum++;
		}
	}


	cout <<"器件个数为："<< truenum << endl;
	//cout << stats << endl;//打印特征矩阵的值用于特征选择调试

	namedWindow("out", WINDOW_NORMAL);
	imshow("out", output);
	waitKey(0);
	return 0;

}