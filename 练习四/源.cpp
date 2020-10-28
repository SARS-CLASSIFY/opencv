#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat frame;
	Mat grayimg;
	VideoCapture cap(0);
	while (1) {
		Mat grad_x, grad_y;
		Mat outimgx,outimgy;
		cap >> frame;
		cvtColor(frame, grayimg, COLOR_BGR2GRAY);


		Sobel(frame, grad_x, CV_16SC1, 1, 0, 3);
		convertScaleAbs(grad_x, outimgx);

		Sobel(frame, grad_y, CV_16SC1, 0, 1, 3);
		convertScaleAbs(grad_y, outimgy);

		imshow("frame",frame);
		imshow("outx", outimgx);
		imshow("outy", outimgy);
		waitKey(30);

	}
	return 0;
}