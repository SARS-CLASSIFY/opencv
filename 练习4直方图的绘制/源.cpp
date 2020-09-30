#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "mycalhist.h"
using namespace cv;
using namespace std;   
/**
  *brief���ͼ����ͨ��ֱ��ͼ���������鼰��ʾ
**/
int main()
{
	Mat srcimg = imread("D:/1.jpg");//·���Զ���
	float histgram_R[256] = { 0 }, histgram_G[256] = { 0 }, histgram_B[256] = { 0 };
	mycalchist(srcimg, histgram_R, histgram_G, histgram_B);

	for (int m = 0;m < 256;m++) {	//��������ʾ
		cout << fixed << setprecision(5) << histgram_R[m] << ' ' << histgram_G[m] << ' ' << histgram_B[m] << endl;
	}

	return(0);


}
