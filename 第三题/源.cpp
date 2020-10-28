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
		GaussianBlur(frame, outimg, Size(3, 3),3,0,BORDER_DEFAULT);

		imshow("out", outimg);
		waitKey(30);

	}
	return 0;
}