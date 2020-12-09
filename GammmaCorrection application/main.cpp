#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "myGammaCorrection.h"
using namespace std;
using namespace cv;

extern unsigned char  Lut[256];


int main()
{

	Mat src = imread("example.jpg");
	Mat dst,dstgray,dst1;
	src.copyTo(dst);

	creat_Lut(Lut, 1/6.5);
	MyGammaCorrection(src, dst, Lut);
	cvtColor(dst, dstgray, CV_BGR2GRAY);//×ª»Ò¶ÈÍ¼

	dstgray.copyTo(dst1);


	/**
	CV_Assert(src.depth() != sizeof(uchar));
	MatIterator_<uchar> itx, endx;
	for (itx = dst1.begin<uchar>(), endx = dst1.end<uchar>(); itx != endx; itx++) {
		if (*itx >= 38 && *itx <= 44) {
			*itx = 255;
		}
		else {
			*itx = 0;
		}

	}*/

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	return 0;


}