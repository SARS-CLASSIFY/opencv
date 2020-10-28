#include <iostream>
#include <opencv2/opencv.hpp>
#include <imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat frame;
	VideoCapture cap(0);
	while (1) {
		Mat outimg;
		cap >> frame;
		blur(frame,outimg,Size(3,3),Point(-1,-1),BORDER_DEFAULT);


		imshow("out", outimg);
		waitKey(30);

	}
	return 0;
}