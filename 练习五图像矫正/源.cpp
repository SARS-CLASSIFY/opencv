#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat srcimg = imread("1.jpg");
	Mat grayimg, binaryimg, dstimg;
	cvtColor(srcimg, grayimg, COLOR_BGR2GRAY);
	threshold(grayimg, binaryimg, 245, 255, THRESH_BINARY);
	int i, x1, y1, x2, y2, x3, y3;
	int height = binaryimg.rows;
	int width = binaryimg.cols;

	//find three points
	for (i = 0;i < width;i++) {
		if (binaryimg.at<uchar>(0, i) == 0) {
			x1 = i;
			y1 = 0;
			break;
		}
	}
	for (i = 0;i < height;i++) {
		if (binaryimg.at<uchar>(i, 0) == 0) {
			x2 = 0;
			y2 = i;
			break;
		}	
		
	}

	for (i = 0;i < height;i++) {
		if (binaryimg.at<uchar>(i,width-1) == 0) {
			x3 = width-1;
			y3 = i;
			break;
		}

	}

	//Corresponding point coordinates
	cv::Point2f pts1[] = {
						cv::Point2f(x1, y1),
						cv::Point2f(x2, y2),
						cv::Point2f(x3, y3),
	};
	cv::Point2f pts2[] = {
							cv::Point2f(0, 0),
							cv::Point2f(0, 315),
							cv::Point2f(313, 0),
	};

	//get matrix
	const cv::Mat affine_matrix = cv::getAffineTransform(pts1, pts2);
	
	//transform
	cv::warpAffine(srcimg, dstimg, affine_matrix, srcimg.size());

	imshow("dst", dstimg);
	waitKey(0);

	return 0;



}