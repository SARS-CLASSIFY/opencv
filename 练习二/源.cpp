#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat dstMat;
	cv::Mat srcMat = cv::imread("1.jpg");
	if (srcMat.empty()) return -1;

	//ROTATE40бу
	float angle = -10.0, scale = 1;
	//imagecenter as rotation center
	cv::Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);
	//get the convert matrix
	const cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);

	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	cv::waitKey(0);

}