#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	float angle = -10.0, scale = 1;
	cv::Mat dstMat;
	cv::Mat src = imread("1.jpg");
	if (src.empty())	return -1;

	//get center
	cv::Point2f center(src.cols / 2.0, src.rows / 2.0);
	//get matrix
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, scale);
	//获取外接四边形
	cv::Rect bbox = cv::RotatedRect(center, src.size(), angle).boundingRect();
	//调整仿射矩阵参数
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	//仿射变换

	cv::warpAffine(src, dstMat, rot, bbox.size());

	cv::imshow("src", src);
	cv::imshow("dst", dstMat);
	cv::waitKey(0);
	return 0;
}