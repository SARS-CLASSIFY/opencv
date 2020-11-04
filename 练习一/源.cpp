#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat srcimg = imread("1.jpg");
	Mat output;
	Canny(srcimg,output,150,100,3);

	imshow("output", output);
	waitKey(0);
	return 0;

}