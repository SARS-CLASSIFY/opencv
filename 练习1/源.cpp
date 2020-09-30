#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	cv::Mat src_color = imread("1.jpg");
	std::vector<cv::Mat> channels;
	cv::split(src_color, channels);
	cv::Mat B = channels.at(0);
	cv::Mat G = channels.at(1);
	cv::Mat R = channels.at(2);
	namedWindow("red", WINDOW_NORMAL);
	namedWindow("blue", WINDOW_NORMAL);
	namedWindow("green", WINDOW_NORMAL);
	namedWindow("origin image", WINDOW_NORMAL);
	imshow("red", R);
	imshow("blue", B);
	imshow("green", G);
	imshow("origin image", src_color);
	waitKey(0);
	return (0);

}