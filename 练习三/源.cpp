#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	cv::Mat dstMat;
	cv::Mat srcMat = imread("1.jpg");
	if (srcMat.empty())	return -1;

	//the three point before affine transformation
	const cv::Point2f src_pt[] = {
									cv::Point2f(200,200),
									cv::Point2f(250,200),
									cv::Point2f(200,100), };
	const cv::Point2f dst_pt[] = {
								cv::Point2f(300,100),
								cv::Point2f(300,50),
								cv::Point2f(200,100), };
	//calculate affine matrix
	const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_pt);

	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());

	namedWindow("dst", WINDOW_NORMAL);
	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	cv::waitKey(0);

}