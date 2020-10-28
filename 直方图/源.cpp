#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture capture(0);
	
	//ÊÓÆµ²¶»ñ
	while (1) {
		Mat myframe;
		capture >> myframe;
		Mat outimg;
		medianBlur(myframe, outimg, 15);
		imshow("out", outimg);
		imshow("cap", myframe);
		waitKey(30);

	}
	return 0;



	

}