#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat frame;
	VideoCapture cap(0);
	while (1) {
		Mat outimg;
		cap >> frame;
		medianBlur(frame, outimg, 15);

		imshow("out", outimg);
		waitKey(30);

	}
	return 0;
}