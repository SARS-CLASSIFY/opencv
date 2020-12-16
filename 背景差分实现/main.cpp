#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main()
{

	Mat myframe, grayframe, bgMat, subMat, bny_subMat;
	VideoCapture capture(0);
	int cnt = 0;
	while(1){


		capture >> myframe;
		cvtColor(myframe, grayframe, CV_BGR2BGRA);
		if (cnt == 0) {
			grayframe.copyTo(bgMat);
		}
		else {
			absdiff(grayframe, bgMat, subMat);

			threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);
			imshow("subMat", subMat);
			imshow("src", myframe);
			imshow("bny_subMat", bny_subMat);
			waitKey(30);
		}
		cnt++;
	}
	return 0;

}