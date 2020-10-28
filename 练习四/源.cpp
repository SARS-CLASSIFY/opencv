#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat frame;
	VideoCapture cap(0);
	while (1) {
		Mat outimgx,outimgy;
		cap >> frame;
		Sobel(frame, outimgx, CV_16SC1, 1, 0, 3);
		Sobel(frame, outimgy, CV_16SC1, 0, 1, 3);

		imshow("outx", outimgx);
		imshow("outy", outimgy);
		waitKey(30);

	}
	return 0;
}