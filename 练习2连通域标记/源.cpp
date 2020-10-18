#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <imgproc.hpp>
using namespace std;
using namespace cv;

int main()
{
	int i,j;
	Mat srcimg = imread("C://Users//86150//Desktop//1.jpg");
	Mat grayimg, binaryimg;
	Mat labels,stats,centroids;
	Mat outputimg;
	srcimg.copyTo(outputimg);
	cvtColor(srcimg, grayimg, CV_BGR2GRAY);
	threshold(grayimg, binaryimg, 90, 255, THRESH_BINARY);

	int commontnum;
	commontnum = connectedComponentsWithStats(binaryimg,labels,stats,centroids,8,CV_32S);
	/******矩形框限定******/	
	for (int i = 0;i < commontnum;i++)
	{
		Rect rec;
		rec.x = stats.at<int>(i, 0);
		rec.y = stats.at<int>(i, 1);
		rec.width = stats.at<int>(i, 2);
		rec.height = stats.at<int>(i, 3);

		rectangle(binaryimg,rec, Scalar(255));
	}
	

	namedWindow("输出结果", WINDOW_NORMAL);
	imshow("输出结果",binaryimg);
	cout <<"连通域个数为："<< commontnum-1 << endl;
	//cout << stats << endl;
	waitKey(0);
	return 0;

}