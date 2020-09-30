#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "mycalhist.h"
using namespace cv;
using namespace std;   
/**
  *brief算出图像三通道直方图并存入数组及显示
**/
int main()
{
	Mat srcimg = imread("D:/1.jpg");//路径自定义
	float histgram_R[256] = { 0 }, histgram_G[256] = { 0 }, histgram_B[256] = { 0 };
	mycalchist(srcimg, histgram_R, histgram_G, histgram_B);

	for (int m = 0;m < 256;m++) {	//结果输出显示
		cout << fixed << setprecision(5) << histgram_R[m] << ' ' << histgram_G[m] << ' ' << histgram_B[m] << endl;
	}

	return(0);


}
