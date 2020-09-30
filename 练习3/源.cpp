#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat srcImage = imread("1.jpg");
	cv::Point pt,pt1,pt2;
	cv::Rect rec;
	rec.width = 100;
	rec.height = 100;
	rec.x = 100;
	rec.y = 100;
	pt.x = 250;
	pt.y = 250;
	pt1.x = 50;
	pt1.y = 50;
	pt2.x = 300;
	pt2.y = 300;
	circle(srcImage, pt, 50, CV_RGB(255, 0, 0), -1, 8, 0);
	line(srcImage, pt1,pt2, CV_RGB(255, 0, 0), 1, 8, 0);
	rectangle(srcImage, rec, CV_RGB(255, 0, 0), -1, 8, 0);




	//namedWindow("img", WINDOW_NORMAL);
	cv::imshow("img",srcImage);
	waitKey(0);

	return(0);
}