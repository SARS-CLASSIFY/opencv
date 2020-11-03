#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	VideoCapture cap (0);
	Mat frame;//video frame
	//personal threshold value define
	double i_minH = 0;
	double i_maxH = 20;
	//0-255
	double i_minS = 43;
	double i_maxS = 255;
	//0-255
	double i_minV = 55;
	double i_maxV = 255;
	Mat hsvMat;//hsvimg
	Mat detectMat,opposit_detectimg;//detected img with the range in person face 
	Mat finalimg;
	while (1) {
		cap >> frame;

		cvtColor(frame, hsvMat, COLOR_BGR2HSV);//convert to HSV img

		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);//HSVrange in human face
		opposit_detectimg = 255 - detectMat;
		//the detectMat chosen as mask
		Mat maskimg,opposit_maskimg,outimg;
		frame.copyTo(maskimg, detectMat);// frame as srcimg,detectMat as mask,maskimg as the out put
		frame.copyTo(opposit_maskimg, opposit_detectimg);//get the background area


		//using medidan filtering to smooth the skin
		medianBlur(maskimg,outimg,11);//smooth

		//final outputimg
		addWeighted(outimg, 1, opposit_maskimg, 1, 0, finalimg);

		imshow("frame", frame);
		imshow("final_img", finalimg);

		waitKey(30);

	}

	return 0;
}